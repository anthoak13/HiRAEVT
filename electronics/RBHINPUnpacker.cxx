//#include <config.h>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stdexcept>

#include </usr/opt/nscldaq/current/include/CFatalException.h>

#include "RBHINPUnpacker.h"

using namespace std;

const Int_t XLM1 =  0x1ff3;
const Int_t XLM2 =  0x2ff3;

static UInt_t numChips;

//______________________________________________________________________________
RBHINPUnpacker::RBHINPUnpacker(const char* name, Int_t nMBs, Bool_t usingSISFADC)
:fFoundBeginMarker(0),fReportNExtraMarkers(0),fTotalUnpackedData(0),fFaultyCount(0),fErrorCount(0),fChName(name)
{
  // --
  //

  SetGeo(-1);
  fnMBs         = nMBs;

  fUsingSISFADC = usingSISFADC;

  fNUnpackedEvents = 0;
}


//______________________________________________________________________________
RBHINPUnpacker::~RBHINPUnpacker()
{
  // --
  //

  Clear();
}


//______________________________________________________________________________
void RBHINPUnpacker::Clear(Option_t *option)
{
  // --
  //

  if(strcmp(option,"A")==0) fNUnpackedEvents = 0;
  fHits.fNHits=0;
}


//______________________________________________________________________________
void RBHINPUnpacker::InitBranch(TTree *tree)
{
  // --
  //
  if(GetFillData()){
    tree->Branch(fChName+".","RBHINPHit",&fHits,32768,2);
  }else{
    cout << "-->RBHINPUnpacker::InitBranch  Branches will not be created or filled." << endl;
  }
}


//______________________________________________________________________________
void RBHINPUnpacker::InitTree(TTree *tree)
{
  // --
  //

  fChain = tree;
}

//______________________________________________________________________________
void RBHINPUnpacker::AddHit(Int_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch,
                                  UShort_t chip, UShort_t Hi, UShort_t Lo, UShort_t time)
{
  // -- Add an entry to the fHits object increasing of 1 the number of hits
  //

  fHits.fBank       [fHits.fNHits]=bank;
  fHits.fXLMIndex   [fHits.fNHits]=xlm;
  fHits.fChip       [fHits.fNHits]=chip;
  fHits.fChannel    [fHits.fNHits]=ch;
  fHits.fChMismatch [fHits.fNHits]=mismatch;
  fHits.fEnergyHi   [fHits.fNHits]=Hi;
  fHits.fEnergyLo   [fHits.fNHits]=Lo;
  fHits.fTime       [fHits.fNHits]=time;

  fHits.fNHits++;
}

//______________________________________________________________________________
Int_t RBHINPUnpacker::Unpack(vector<UShort_t>& event, UInt_t offset)
{
  // -- Unpacker for NEW HINP. So the comments below are out of date.
  //
  //
  //  ------------------------------------
  // | id 16-bits                         |
  //  ------------------------------------
  // | number of words in the bank        |
  //  ------------------------------------
  // | number of events                   |
  //  ------------------------------------
  // | tag data from XLM1 SRAMa           |
  // |...                                 |
  //  ------------------------------------
  // | number of events                   |
  //  ------------------------------------
  // | tag data from XLM1 SRAMb           |
  // |..                                  |
  //  ------------------------------------
  // | 0xfadc                             |
  //  ------------------------------------
  // | Mask of read groups                |
  //  ------------------------------------
  // | Data from the FADC module group1   |
  //  ------------------------------------
  // | 0xaaa                              |
  //  ------------------------------------
  // |...                                 |
  // | Data from the FADC module group2   |
  // |...                                 |
  //  ------------------------------------
  //
  //

  Clear();

  //  cout << "Starting RBHINPUnpacker::Unpack" << endl;

  /*
  UShort_t         xlmID[10];
  ULong64_t        xlmWordCount[10];
  ULong64_t        xlmChWordCount[10];
  ULong64_t        xlmChMismatchWordCount[10];
  vector<UShort_t> channelIds16[10];
  vector<UInt_t>   channelIds32[10];
  */
  uint32_t  channelId, timeStamp[2], channelCount;
  uint32_t  bumflag=0;
  //uint32_t  XLMID;
  static uint32_t bumcount;
  uint32_t xlmWordCount[10];

  uint32_t  initOffset = offset;  // get initial offset to XLM data packet to later compute end offset


  //Code below based on CHINPA.cpp (by Jon Elson), which unpacks data from the new
  //generation of HINP chips that has both a high and a low gain.
  //-JJM
  for(int bank = 0;bank<fnMBs;bank++)
    {
      //It seems like Jon counts "banks" as simply being the MB numbers...whereas I consider banks
      //to be the banks on the individual XLMs. So for instance, if there were 4 MBs, Jon would count
      //4 banks where as I would count 2 for each XLM.
      int xlmNum = bank/2;

      //cout << "Unpacking bank " << bank << endl;
      //XLMID = event[offset] & 0x3fff;
      /*
      for (int i=0; i<24; i++){
	cout << hex << event[offset+i] << endl;
      }
      */
      //offset = offset + 10;
      //cout << "marker = " << hex << XLMID << endl;
      //cout << "XLM word is " << hex << event[offset] << endl;
      offset +=1;     // skip over HiRA 1ff3 code
      uint32_t  wordCount = getLong(event, offset);
      xlmWordCount[bank]=wordCount;

      //Check if XLM word count is unreasonable
      //12 CBs per MB * 32 channels per CB * 4 words per channel
      // = 1536
      if (xlmWordCount[bank] > 1536) return -1;

      //  printf("wordcount is %d offset is %d\n",wordCount, offset);
      offset+=2;
      //
      // channel counts > 4095 are error indicators..
      // just skip the data the VMUSB can't help but read
      //
      // mask off the upper 16-bit field
      wordCount &= 0xffff;
      channelCount      = event[offset];
      offset += 1;

      // cout << "chanelcount = " << channelCount << endl;
      //  printf("word count is %d, channelCount is %d\n",wordCount,channelCount);
      if (channelCount >4095) {
        fErrorCount++;
        cerr << "Got an error report from "
             << hex << channelCount << dec << endl;
        //    offset += wordCount-1;
        //    printf("wordCount = %d offset = %d\n",wordCount,offset);
        return offset;
      }
      if (wordCount > (wordCount*80+12)) {
        fErrorCount++;
        printf("impossible word count %d offset %d\n",wordCount,offset);
        //    offset += wordCount-1;
        //    printf("wordCount = %d offset = %d\n",wordCount,offset);
        return offset;
      }
      if (channelCount > wordCount*80) {
        fErrorCount++;
        printf("impossible channel count %d offset %d\n",channelCount,offset);
        // offset += wordCount-1;
        //    printf("wordCount = %d offset = %d\n",wordCount,offset);
        return offset;
      }
      // word count must be evenly divisible by 4
      // loop through the groups of 5 words per hit channel
      timeStamp[0]  = getLong(event, offset);
      offset+=2;
      timeStamp[1]  = getLong(event, offset);
      offset+=2;

      //Set the number of chips JJM
      numChips = 28;

      //cout << "Made it past timestamp " << endl;
      //      cout << "Channel count is " << channelCount << endl;
      for (unsigned int i =0; i < channelCount/4; i++) {

	fTotalUnpackedData++;

        // get channel tag
        channelId      = event[offset];
        //    printf("Channel ID = %x\n",channelId);
        offset +=1;
        // now pick up analog data
        uint32_t Hi     = event[offset] & 0x3fff;
        offset += 1;
        uint32_t Lo     = event[offset] & 0x3fff;
        offset += 1;
        uint32_t time  = event[offset] & 0x3fff;
        offset += 1;

        uint32_t channel   = channelId & 0x0f;
        uint32_t chip      = (channelId >> 5) & 0xff;
        //      if ((chip & 0x01) == 0) {channel+=16;}
        uint32_t board     = (chip+1)/2;
        //    convert 16-channel chip ID to 32-channel board ID
        // suppress invalid chip #'s
        //      cout << "CHA CB = " << board << endl;

	//	cout << "About to test chip number " << chip << endl;
        if (chip > 0 && chip <= numChips) {
          //printf("chip %d board %d chan %d Hi %d Lo %d Time %d (numChips=%d)\n",chip,board,channel,Hi,Lo,time,numChips);
          //cout <<"Board = " << board-1 << endl;
          //CTreeParameterArray** pChipTree = myParameters[bank][chip-1];
          //CTreeParameterArray*  pHis       = pChipTree[0];
          //CTreeParameterArray*  pLos       = pChipTree[1];
          //CTreeParameterArray*  pTs       = pChipTree[2];

          //      cout << "channel = " << channel << endl;
          //(*pHis)[channel] = Hi;
          //(*pLos)[channel] = Lo;
          //(*pTs)[channel] = time;

	  //Hacked together for now:
	  Bool_t mismatch = kFALSE;
	  /*
	  cout << "******************" << endl;
	  cout << "About to add hit: " << endl;
	  cout << "xlmNum: " << xlmNum <<  endl;
	  cout << "bank: " << bank <<  endl;
	  cout << "mismatch: " << mismatch <<  endl;
	  cout << "channel: " << channel <<  endl;
	  cout << "chip: " << chip <<  endl;
	  cout << "Hi: " << Hi <<  endl;
	  cout << "Lo: " << Lo <<  endl;
	  cout << "time: " << time <<  endl;
	  cout << "******************" << endl;
	  */
	  AddHit(xlmNum, bank, mismatch, channel, chip, Hi, Lo, time);

          //cout <<"chip = " << dec << chip <<" channel = " << channel << " " << Hi << " " << Lo << " " << time << endl;
        } else {
          bumflag=1;
	  fFaultyCount++;
          printf("faulty chip %d board %d chan %d A %d B %d Time %d (numChips=%d)\n",chip,board,channel,Hi,Lo,time,numChips);
        }
      }


      //  printf("offset at end = %d  ",offset);
      // figure out how much garbage to gobble from end of event
      if (bumflag) {
        bumcount++;
        printf("wordCount %d channelCount %d offset %d bum count %d\n",wordCount,channelCount,offset, bumcount);
        /*
          for (dumpctr=0; dumpctr <= wordCount; dumpctr+=16) {
          printf("dump %d ",dumpctr);
          for (dumpoff=dumpctr; dumpoff < dumpctr+16; dumpoff++)
          printf("%4x  ",event[dumpoff]);
          printf("\n");
          }
	*/
	//        bumflag=0;
      }
      //  printf("offset was %d   initOffset %d channelCount %d ",offset,initOffset,channelCount);
      /*    if ((offset & 0x0001) == 0) {
            offset +=2;
            } else {
            offset += 3;
            }*/
      offset = initOffset + channelCount + 10;
      if ((channelCount &0x0001) != 1) {
        offset +=1;
      }
      //    printf("final offset = %d\n",offset);
    }
  offset=initOffset+6;
  for(int i =0;i<fnMBs;i++)
    {
      offset += xlmWordCount[i];
    }
  if (bumflag) {
    cout << "XLM word count hex" << hex << xlmWordCount[0] << endl;
    cout << "XLM word count hex" << xlmWordCount[1] << endl;
    cout << "XLM word count " << dec <<xlmWordCount[0] << endl;
    cout << "XLM word count " <<  xlmWordCount[1] << endl;

    cout << "Init offset " << initOffset << endl;
    cout << "Returning offset " << offset<< " here" << endl;
    for(int iDump = initOffset; iDump < 10; iDump++){
      printf("%4x  ",event[iDump]);
    }
  }


  return offset;
}

//______________________________________________________________________________
void RBHINPUnpacker::PrintSummary()
{
  printf("-- module %s --\n", fChName.Data());
  printf("%llu total unpacked data\n", fTotalUnpackedData);
  printf("%llu faulty chip errors found\n",fFaultyCount);
  printf("%llu buffer errors found\n",fErrorCount);

  printf("\n");
}

//______________________________________________________________________________
void RBHINPUnpacker::AddTTreeUserInfo(TTree *tree)
{
  TNamed * unpackedData      = new TNamed(Form("module %s : Total Unpacked Data",fChName.Data()), Form("%llu", fTotalUnpackedData));
  TNamed * errorsChipFound   = new TNamed(Form("module %s : Faulty Chip Errors Found",fChName.Data()), Form("%llu", fFaultyCount));
  TNamed * errorsBufFound    = new TNamed(Form("module %s : Buffer Errors Found",fChName.Data()), Form("%llu", fErrorCount));

  tree->GetUserInfo()->Add(unpackedData);         //Total unpacked data in this module
  tree->GetUserInfo()->Add(errorsChipFound);      //Faulty Chip Errors produced
  tree->GetUserInfo()->Add(errorsBufFound);       //Buffer Errors found
}
