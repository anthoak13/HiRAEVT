#include <config.h>
#include "CHINPA.h"
#include <Event.h>
#include <stdint.h>
#include <TreeParameter.h>
#include <iostream>
#include <TCLVariable.h>
#include <TCLList.h>
#include <SpecTcl.h>
#include <stdlib.h>
#include <stdio.h>

#include "CHira.h"

using namespace std;

static uint32_t numChips;


extern class CHira hira;



CHINPA::CHINPA():nMBs(0)
{

}

CHINPA::~CHINPA() {}

/*
**   unpacker:
**   when called first tack a tree parameter array
**   of arrays on to the parameter map
**   so that we can unpack into it.
**   data looks like:
**     Channel count (uint32_t) (>4095  is an error)
**     Channel tag  Chipid (8bits) 0 (1bit) (channel# 4bits)
**        Hiadc(32), LoADC(32), Time(32)
**      ...
**   Note that when processing ADC/TDC data
**   If we run off the end of the event, we just silently stop
**   processing.
**
*/
unsigned int
CHINPA::operator()(CEvent& rEvent,
		  vector<unsigned short>& event,
		  unsigned int            offset,
		  CParamMapCommand::AdcMapping* pMap)
{
  //  printf("*** CHINPA initial offset = %d\n",offset);

  //  cout <<"Hira flag = " << hira.flag << endl;
  if(hira.flag)
    {
      hira.Reset();
      hira.setInvalid();
      hira.clear();
    }


  // cerr << "testing KB " << endl;
  CTreeParameterArray**** myParameters = getTree(pMap, rEvent);

  uint32_t  channelId, timeStamp[2], channelCount;
  uint32_t  dumpctr, dumpoff, bumflag=0;
  uint32_t XLMID;
  static uint32_t bumcount;
  uint32_t xlmWordCount[10];

  uint32_t  initOffset = offset;  // get initial offset to XLM data packet to later compute end offset

  for(int bank = 0;bank<nMBs;bank++)
    {
      XLMID = event[offset] & 0x3fff;
      //      cout << "marker = " << hex << XLMID << endl;
      offset +=1;     // skip over HiRA 1ff3 code
      uint32_t  wordCount = getLong(event, offset);
      xlmWordCount[bank]=wordCount;
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
	cerr << "Got an error report from " << pMap->name << " "
	     << hex << channelCount << dec << endl;
	//    offset += wordCount-1;
	//    printf("wordCount = %d offset = %d\n",wordCount,offset);
	return offset;
      }
      if (wordCount > (wordCount*80+12)) {
	printf("impossible word count %d offset %d\n",wordCount,offset);
	//    offset += wordCount-1;
	//    printf("wordCount = %d offset = %d\n",wordCount,offset);
	return offset;
      }
      if (channelCount > wordCount*80) {
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
      for (int i =0; i < channelCount/4; i++) {
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
	//	if ((chip & 0x01) == 0) {channel+=16;}
	uint32_t board     = (chip+1)/2;
	//    convert 16-channel chip ID to 32-channel board ID
	// suppress invalid chip #'s
	//	cout << "CHA CB = " << board << endl;
	if (chip > 0 && chip <= numChips) {
	  //printf("chip %d board %d chan %d Hi %d Lo %d Time %d (numChips=%d)\n",chip,board,channel,Hi,Lo,time,numChips);
	  //cout <<"Board = " << board-1 << endl;
	  CTreeParameterArray** pChipTree = myParameters[bank][chip-1];
	  CTreeParameterArray*  pHis       = pChipTree[0];
	  CTreeParameterArray*  pLos       = pChipTree[1];
	  CTreeParameterArray*  pTs       = pChipTree[2];

	  //	  cout << "channel = " << channel << endl;
	  (*pHis)[channel] = Hi;
	  (*pLos)[channel] = Lo;
	  (*pTs)[channel] = time;
	  
	  //cout <<"chip = " << dec << chip <<" channel = " << channel << " " << Hi << " " << Lo << " " << time << endl;
	  
	  

      
	} else {
	  bumflag=1;
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
	bumflag=0;
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
  for(int i =0;i<nMBs;i++)
    {
      offset += xlmWordCount[i];
    }
  return offset;
}

/*
** Return the extra data that is the tree parameter for this
** unpacking... creating it if it does not yet exist.
** ..and binding it to the event.
*/

/* KB
CTreeParameterArray***
CHINPA::getTree(CParamMapCommand::AdcMapping* pMap,
	       CEvent& rEvent)
{
  //  cerr << "Entering CHINPA.cpp function CHINPA::getTree\n";
  if (!pMap->extraData) {
    SpecTcl* api             = SpecTcl::getInstance();
    CTCLInterpreter *pInterp = api->getInterpreter();
    string baseName = pMap->name;
    CTCLVariable HINPAChips(pInterp, "HINPAChips",false);
    
    const char* pChipList = 
      HINPAChips.Get(TCL_GLOBAL_ONLY,
		    const_cast<char*>(baseName.c_str()));
    if (!pChipList) {
      cerr << "HINPAChips("<< baseName << ") not defined!!\n";
      exit(-1);
    }
    CTCLList ChipList(pInterp, pChipList);
    StringArray chips;
    ChipList.Split(chips);

    CTreeParameterArray*** chipArray = 
      new CTreeParameterArray**[chips.size()];
    numChips = chips.size();   // leave valid range of chips for unpacker
    cerr << "numChips = " << numChips << endl;
    pMap->extraData = chipArray;
    
    // Iterate over the chips making Hi, Lo and T tree parameter
    // arrays.

    cerr << "HINPA GetTree, chips.size = " << chips.size() << endl;
    for (int i =0; i < chips.size(); i++) {
      cerr << "creating chip # " << i+1 << endl;
      char chipNumber[100];
      sprintf(chipNumber, "%02d", atoi(chips[i].c_str()));
      CTreeParameterArray** teArray = new CTreeParameterArray*[3];
      chipArray[i] = teArray;
      string HiBaseName = baseName;
      HiBaseName += ".Hi.";
      HiBaseName += chipNumber;
      teArray[0] = new CTreeParameterArray(HiBaseName,
				      14, 32, 0);
      string LoBaseName = baseName;
      LoBaseName += ".Lo.";
      LoBaseName += chipNumber;
      teArray[1] = new CTreeParameterArray(LoBaseName,
				      14, 32, 0);

      string tBaseName = baseName;
      tBaseName += ".t.";
      tBaseName += chipNumber;
      teArray[2] = new CTreeParameterArray(tBaseName,
				      14, 32, 0);
    }
    
    CTreeParameter::BindParameters();
    CTreeParameter::setEvent(rEvent);
  }
  return reinterpret_cast<CTreeParameterArray***>(pMap->extraData);
}
*/
//CTreeParameterArray****
//CHINPA::getTree(CParamMapCommand::AdcMapping* pMap,
//		CEvent& rEvent)
CTreeParameterArray****
CHINPA::getTree(CParamMapCommand::AdcMapping* pMap,
	       CEvent& rEvent)
{
  if (!pMap->extraData) {
    SpecTcl         *api      = SpecTcl::getInstance();
    CTCLInterpreter *pInterp  = api->getInterpreter();
    string           baseName = pMap->name;
    CTCLVariable HINPAChips(pInterp, "HINPAChips",false);
    CTCLVariable HINPAMBs  (pInterp, "HINPAMBs",false);
    
    const char* pChipList = HINPAChips.Get(TCL_GLOBAL_ONLY, const_cast<char*>(baseName.c_str()));
    const char* pMBList   = HINPAMBs.Get  (TCL_GLOBAL_ONLY, const_cast<char*>(baseName.c_str()));
    
    if (!pChipList) {
      cerr << "HINPAChips("<< baseName << ") not defined!!\n";
      exit(-1);
    }
    if (!pMBList) {
      cerr << "HINPAMBs("<< baseName << ") not defined!!\n";
      exit(-1);
    }
    CTCLList ChipList(pInterp, pChipList);
    StringArray chips;
    ChipList.Split(chips);

    // Define the number of motherboards that are used.
    CTCLList MBList(pInterp, pMBList);
    StringArray mbNames;
    MBList.Split(mbNames);
    cout << "\n-->CHINP:: " << mbNames.size() << " motherboards defined in specconfig.tcl" << endl;
    nMBs = mbNames.size();
    
    CTreeParameterArray **** mbArray = new CTreeParameterArray***[nMBs];
    //    cout << "nMBs = " << nMBs << " chipsize " << chips.size() << endl;
    for(int mb=0; mb<nMBs; mb++){
      CTreeParameterArray*** chipArray =  new CTreeParameterArray**[chips.size()];
      numChips    = chips.size();           // leave range of chips for unpacker
      mbArray[mb] = chipArray;
      
      // Iterate over the chips making an E and T tree parameter array.
      for (int i =0; i < chips.size(); i++) {
        char bname[100];
        sprintf(bname,"mb%i",mb+1);
        
        char chipNumber[100];
        sprintf(chipNumber, "%02d", atoi(chips[i].c_str()));
        CTreeParameterArray** teArray = new CTreeParameterArray*[3];
        chipArray[i] = teArray;
        string eBaseName = baseName;
        eBaseName += ".";
        eBaseName += string(bname);
        eBaseName += ".e.";
        eBaseName += chipNumber;
        teArray[0] = new CTreeParameterArray(eBaseName,
                        14,
                        32, 0);
        string eLoBaseName = baseName;
        eLoBaseName += ".";
        eLoBaseName += string(bname);
        eLoBaseName += ".eLo.";
        eLoBaseName += chipNumber;
        teArray[1] = new CTreeParameterArray(eLoBaseName,
                        14,
                        32, 0);
        string tBaseName = baseName;
        eBaseName += ".";
        eBaseName += string(bname);
        tBaseName += ".t.";
        tBaseName += chipNumber;
        teArray[2] = new CTreeParameterArray(tBaseName,
                        14, 32, 0);
        
      }
      
      CTreeParameter::BindParameters();
      CTreeParameter::setEvent(rEvent);
    }
    pMap->extraData = mbArray;
  }
  
  return reinterpret_cast<CTreeParameterArray****>(pMap->extraData);
}
