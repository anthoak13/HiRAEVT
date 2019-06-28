//
//  RBCAEN7xxUnpacker.cpp
//

//#include <config.h>
#include "RBCAEN7xxUnpacker.h"
//#include <Event.h>
//#include <stdint.h>
#include <iostream>

using namespace std;

ClassImp(RBCAEN7xxUnpacker)

// Constants:

// All data words have these bits:

static const UInt_t ALLH_TYPEMASK(0x7000000);
static const UInt_t ALLH_TYPESHIFT(24);
static const UInt_t ALLH_GEOMASK(0xf8000000);
static const UInt_t ALLH_GEOSHIFT(27);

// High part of header.

static const UInt_t HDRH_CRATEMASK(0x00ff0000);
static const UInt_t HDRH_CRATESHIFT(16);

// Low part of header.
static const UInt_t HDRL_COUNTMASK(0X3f00);
static const UInt_t HDRL_COUNTSHIFT(8);

// High part of data:

static const UInt_t DATAH_CHANMASK(0x3f0000);
static const UInt_t DATAH_CHANSHIFT(16);

// Low part of data

static const UInt_t DATAL_UNBIT(0x2000);
static const UInt_t DATAL_OVBIT(0x1000);
static const UInt_t DATAL_VBIT(0x40000);
static const UInt_t DATAL_DATAMASK(0x0fff);

//  High part of trailer:- index in event to the first unprocessed word of the event.

static const UInt_t TRAILH_EVHIMASK(0x00ff0000);

// Word types:

static const UInt_t HEADER(2);
static const UInt_t DATA(0);
static const UInt_t TRAILER(4);
static const UInt_t INVALID(6);



/////////////////////////////////////////////////////////////////////
// Canonicals..

/*!
 Construction is a no-op.

 */
//RBCAEN7xxUnpacker::RBCAEN7xxUnpacker() {}

/*!
 Destruction is a no-op.
 */
//______________________________________________________________________________
RBCAEN7xxUnpacker::RBCAEN7xxUnpacker(const char *chName)
:fChName(chName),fnCh(32),fTotalUnpackedCount(0),fOverflowCount(0),fVSNMismatchCount(0)
{
  // --
  //

  SetEnabled(kTRUE);
  SetFillData(kTRUE);

  SetBranchName(chName);

  Clear();
}


//______________________________________________________________________________
RBCAEN7xxUnpacker::~RBCAEN7xxUnpacker() {}


//______________________________________________________________________________
void RBCAEN7xxUnpacker::Clear(Option_t *option)
{
   for(int i=0; i<fnCh; i++) {
     fData[i]=-9999;
   }
}


//______________________________________________________________________________
void RBCAEN7xxUnpacker::InitClass()
{}

//______________________________________________________________________________
void RBCAEN7xxUnpacker::InitBranch(TTree *tree)
{
  if(GetFillData()){
    tree->Branch(fChName, fData, Form("%s[%i]/S",fChName.Data(),fnCh));
  }else{
    cout << "-->RBCAEN7xxUnpacker::InitBranch  Branches will not be created or filled." << endl;
  }
}


//______________________________________________________________________________
void RBCAEN7xxUnpacker::InitTree(TTree *tree)
{
  fChain = tree;
}


//////////////////////////////////////////////////////////////////////
//  Virtual function overrides

/*!
 Perform the unpack.
 - If we are not pointing to the header corresopnding to our ADC,
 skip out without doing anything.
 - For all data words, until we see a non data word;
 extract the data -> the parameter index indicated by our parameter map.

 \param rEvent  - The event we are unpacking.
 \param event   - References the vector containing the assembled event
 (the internal segment headers have been removed).
 \param offset  - Index in event to our chunk.
 \param pMap    - Pointer to our parameter map.  This contains our VSN and map of channel->
 parameter id (index in rEvent).

 \return unsigned int
 \retval offset to the first word of the event not processed by this member.

 \note - Overflow and Underflow parameters are not transferred to parameters.
 \note - the data are in little-endian form.
 */
//______________________________________________________________________________
Int_t RBCAEN7xxUnpacker::Unpack(vector<UShort_t>& event, UInt_t offset)
{
  Clear();

  // DEBUG
//   printf("called RBCAEN7xxUnpacker::Unpack(vector<UShort_t>& event, UInt_t offset)\n");

  // Get the 'header' .. ensure that it is one and that it matches our VSN.
  unsigned long header  = getLong(event, offset);
  int vsn = DecodeVSN(header);

  if(vsn != GetVSN()) {
    cerr << "VSN wrong: " << vsn << " " << GetVSN() << std::endl;
    fVSNMismatchCount++;
    return offset;
  }

  // If we do not have a VSN and all we have are 0xffff's then return.
  if(GetVSN()==-1 && event[offset]==0xffff && event[offset+1]==0xffff) return offset+2;

  // Ok this is our data:
  offset += 2;			// Next longword..

  // I've seen cases where all I get is a _trailer_.. in that case
  // we're done so skip the analysis:
  if (((header & ALLH_TYPEMASK) >> ALLH_TYPESHIFT) != TRAILER) {
    unsigned long datum   = getLong(event, offset);
    offset += 2;			// skip even if its not a data long as it's a trailer then.

    while (((datum & ALLH_TYPEMASK) >> ALLH_TYPESHIFT) == DATA) {
      bool underflow = (datum & DATAL_UNBIT) != 0;
      bool overflow  = (datum & DATAL_OVBIT) != 0;

      fTotalUnpackedCount++;

      //Edited by JJM May 2016
      //Adjusting treatment of overflow events
      if (!underflow) {
	if (!overflow) {
	  int channel = (datum & DATAH_CHANMASK) >> DATAH_CHANSHIFT;
	  int value   = datum & DATAL_DATAMASK;
	  fData[channel] = value;

//           printf("setting %d channel to %d value\n",channel, value);
//           printf("the value was %lu\n",datum & DATAL_DATAMASK);

	  //	  cout << value << " ";
	} else {
	  fOverflowCount++;
	  int channel = (datum & DATAH_CHANMASK) >> DATAH_CHANSHIFT;
	  int value   = 4096;
	  fData[channel] = value;

//           printf("setting %d channel to %d value\n",channel, value);

	  //	  cout << value << " ";
	}
      }

      datum = getLong(event, offset);
      offset += 2;
    }

    // And damned if I havn't seen duplicated trailers as well so:
    while(((datum & ALLH_TYPEMASK) >> ALLH_TYPESHIFT) == TRAILER) {
      datum = getLong(event,offset);
      offset += 2;
    }
    offset -= 2;		// Don't count the non trailer longword.
  }

  // An extra 32 bits of 0xffffffff was read if not in a chain or if at
  // end of chain:
  if (getLong(event, offset) == 0xffffffff) {
    offset += 2;
  }

  return offset;
}

//______________________________________________________________________________
Int_t RBCAEN7xxUnpacker::DecodeVSN(Int_t header)
{
  // --
  //
  return ((header & ALLH_GEOMASK) >> ALLH_GEOSHIFT);
}

//______________________________________________________________________________
void RBCAEN7xxUnpacker::PrintSummary()
{
  printf("-- module %s --\n", fChName.Data());
  printf("%llu total unpacked data\n",fTotalUnpackedCount);
  printf("%llu VSN mismatches found\n",fVSNMismatchCount);
  printf("%.1f %% overflows data\n", 100*double(fOverflowCount)/double(fTotalUnpackedCount));
  printf("\n");
}

//______________________________________________________________________________
void RBCAEN7xxUnpacker::AddTTreeUserInfo(TTree *tree)
{
  TNamed * unpackedData      = new TNamed(Form("module %s : Total Unpacked Data",fChName.Data()), Form("%llu", fTotalUnpackedCount));
  TNamed * VSNMismatches     = new TNamed(Form("module %s : VSN Mismatches",fChName.Data()), Form("%llu", fVSNMismatchCount));
  TNamed * overflowsFound    = new TNamed(Form("module %s : %% Overflow Data",fChName.Data()), Form("%.1f", 100*double(fOverflowCount)/double(fTotalUnpackedCount)));

  tree->GetUserInfo()->Add(unpackedData);       //Total unpacked data in this module
  tree->GetUserInfo()->Add(VSNMismatches);      //Number of VSN Mismatches
  tree->GetUserInfo()->Add(overflowsFound);     //Percentage of Overflows found
}
