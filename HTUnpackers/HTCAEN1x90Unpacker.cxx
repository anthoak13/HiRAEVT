//
//  HTCAEN1x90Unpacker.cpp
//

#include "HTCAEN1x90Unpacker.h"

////////////////////////////////////////////////////////////////////
//
// Constants that define the fields we need to see in the
// TDC longwords:
//

// Item type field and possible values:

static const UInt_t ITEM_TYPE = 0xf8000000;     // Item type field.
static const UInt_t TYPE_GBLHEAD = 0x40000000;  // global header type
static const UInt_t TYPE_TDCHEAD = 0x08000000;  // TDC chip header data.
static const UInt_t TYPE_DATA = 0x00000000;     // Tdc data.
static const UInt_t TYPE_TDCTRAIL = 0x18000000; // TDC Trailer.
static const UInt_t TYPE_ERROR = 0x20000000;    // TDC error word.
static const UInt_t TYPE_TRIGTIME = 0x88000000; // Extended trigger time.
static const UInt_t TYPE_GBLTRAIL = 0x80000000; // Global trailer (end of TDC data).

// What we care about in the gbl header:

static const UInt_t GBLHEAD_VSN = 0x0000001f; // Mask for virtual slot number.

// What we care about in the ERROR words:

static const UInt_t ERROR_TDCMASK = 0x03000000; // Mask of TDC chip number.
static const UInt_t ERROR_TDCSHIFT = 24;
static const UInt_t ERROR_BITS = 0x00007fff; // Mask of error bits.

static const char *ERROR_STRINGS[] = {"Hit lost in group 0 from read-out FIFO overflow.",
                                      "Hit lost in group 0 from L1 overflow.",
                                      "Hit error has been detected in group 0.",
                                      "Hit lost in group 1 from read-out FIFO overflow,",
                                      "Hit lost in group 1 from L1 overflow",
                                      "Hit error has been detected in group 1",
                                      "Hit lost in group 2 from read-out FIFO overflow,",
                                      "Hit lost in group 2 from L1 overflow",
                                      "Hit error has been detected in group 2",
                                      "Hit lost in group 3 from read-out FIFO overflow,",
                                      "Hit lost in group 3 from L1 overflow",
                                      "Hit error has been detected in group 3",
                                      "Hits rejected because of programmed event size limit",
                                      "Event lost (trigger FIFO overflow",
                                      "Internal Fatal Chip error has been detected"};

#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"

#include <exception>
#include <iostream>

#include "nlohmann/json.hpp"
using namespace std;

HTCAEN1x90Unpacker::HTCAEN1x90Unpacker(json moduleDescription)
   : fTotalUnpackedData(0), fErrorCount(0), fNoReferenceCount(0), fVSNMismatchCount(0)
{
   // Get data from JSON
   TString name = moduleDescription["moduleName"].get<std::string>();
   SetVSN(moduleDescription["vsn"].get<int>());
   fnChannels = moduleDescription["numberCh"].get<int>();
   fRefChannel = moduleDescription["refCh"].get<int>();
   fChsToNs = moduleDescription["nsPerCh"].get<double>();
   kSingleHit = moduleDescription.value("singleHit", false);

   if (fnChannels > 128)
      throw std::runtime_error("Cannot support more than 128 channels in CAEN 1x90 tdc!");

   fRandomGen = new TRandom3(0);
   if (kSingleHit)
      fModule = new HTRootCAEN1x90SingleHit(name);
   else
      fModule = new HTRootCAEN1x90(name);

   switch (fnChannels) {
      // V1190: 18 bits of data then 7 bits of channel number:
   case 128:
   case 64:
      fChanmask = 0x03f80000;
      fChanshift = 19;
      fDatamask = 0x0007ffff;
      break;
      // V1290: 20 bits of data then 5 bits of channel number:
   case 32:
   case 16:
      fChanmask = 0x03e00000;
      fChanshift = 21;
      fDatamask = 0x001fffff;
      break;
      // Illegal values
   default:
      std::cerr << "-->HTCAEN1x90  mis configured. \n";
      std::cerr << "  -fnChannels must be one of 16,32,64 or 128 but was: " << fnChannels << std::endl;
   }
}

/*!
 Destruction is a no-op.
 */
//______________________________________________________________________________
HTCAEN1x90Unpacker::~HTCAEN1x90Unpacker()
{
   delete fRandomGen;
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
Int_t HTCAEN1x90Unpacker::Unpack(vector<UShort_t> &event, UInt_t offset)
{
   // Create a nice pointer to the module
   fModule->Clear();

   vector<Int_t> rawTimes[128]; //  Raw times are stored here pending ref time subtraction.

   // If this chunk of the event is for us, there should be a TDC global header,
   // and it should have a geo field that matches the vsn in our pMap element.
   UInt_t header = getLong(event, offset);
   auto origOffset = offset;

   if ((header & ITEM_TYPE) != TYPE_GBLHEAD) {
      cerr << "Not TDC Data" << endl;

      PrintHex(event, offset, event.size());
      return offset; // not TDC data.
   }

   if ((header & GBLHEAD_VSN) != GetVSN()) {
      cerr << "Failed to find TDC: " << (header & GBLHEAD_VSN) << endl;
      fVSNMismatchCount++;
      return offset;
   }

   // Now unpack the data:

   offset += 2;                     // 2 words / long
   size_t maxoffset = event.size(); // protection against malformed data.

   // We're really only interested in the following data types:
   // TDC data,
   //

   bool done = false;
   int totalHits = 0;
   while ((offset < maxoffset) && !done) {

      UInt_t datum = getLong(event, offset);
      if (datum == 0xffffffff)
         break; // premature end of event.

      // Record we found a long to examine
      offset += 2;

      switch (datum & ITEM_TYPE) {
         // Ignored types:
      case TYPE_TDCHEAD:
      case TYPE_TDCTRAIL:
      case TYPE_TRIGTIME:
         break;
         // The GBLTRAIL type  bounces us out of the loop:

      case TYPE_GBLTRAIL:
         // Skip any extra events. I think this is from the event buffer.
         while (event[offset] != 0xffff && offset < maxoffset)
            offset++;

         done = true;
         break;

         // The error type prints out an error message:
      case TYPE_ERROR:
         fErrorCount++;
         reportError(datum, GetVSN());
         break;

         // TDC data must be extracted and histogrammed.

      case TYPE_DATA:
         UInt_t channel = (datum & fChanmask) >> fChanshift;
         UInt_t time = datum & fDatamask;

         // Store the raw times in a temp vector
         rawTimes[channel].push_back(time);
         totalHits++;
         break;
      }
   }

   // Print the data unpacked
   // std::cout << "HTCAEN1x90Unpacker: " << std::endl;
   // PrintHex(event, origOffset, offset - origOffset);

   // If we got no hits (just tdc headers/trailers don't do anything.
   if (totalHits <= 0)
      return offset;

   // Each totalHit is a long (two words)
   fTotalUnpackedData += totalHits;

   //
   // Two cases to consider.  If the reference channel number is -1
   // there's no reference channel..otherwised there is:
   //
   Int_t refTime = 0;      // Default to no reference chhanel:
   if (fRefChannel >= 0) { //  Reference channel used:

      if (rawTimes[fRefChannel].size() > 0)
         refTime = rawTimes[fRefChannel][0];
      else {
         fNoReferenceCount++;
         // std::cerr << "-- TDC data with no hits in reference time discarded from vsn: ";
         // std::cerr << GetVSN() << std::endl;
         return offset;
      }
   }

   // The reftime defaults to zero which essentially does not adjust the times
   // if no reference channel is specified.

   for (int i = 0; i < fnChannels; i++)
      for (auto &rawTime : rawTimes[i]) {
         // Get rid of random gen noise
         // if(triggerRelative!=0)
         // triggerRelative += fRandomGen->Rndm()-0.5;

         Double_t calTime = fChsToNs * (rawTime - refTime);
         if (kSingleHit) {
            dynamic_cast<HTRootCAEN1x90SingleHit *>(fModule)->SetData(i, calTime);
            break;
         } else
            dynamic_cast<HTRootCAEN1x90 *>(fModule)->SetNextData(i, calTime);
      } // End loop over hits

   return offset;
}

///////////////////////////////////////////////////////////////////////////
//// Utility functions:
////
//
//
//______________________________________________________________________________
Int_t HTCAEN1x90Unpacker::DecodeVSN(Int_t header)
{
   // --
   //
   return (header & GBLHEAD_VSN);
}

///*
// ** Get the information about a TDC.
// ** If necessary we'll create new information and
// ** link it to the mapping array first.
// */
// CV1x90Unpacker::TdcInfo&
// CV1x90Unpacker::getInfo(CParamMapCommand::AdcMapping* pMap)
//{
//  if (!pMap->extraData) {
//    pMap->extraData =  newTdc(pMap->name);
//  }
//  return *reinterpret_cast<TdcInfo*>(pMap->extraData);
//}
//
///*
// ** Report error information from a TDC (to stderr).
// **
// ** Parameters:
// **   errorWord A TDC error word.  THe bottom 14 bits are the error info.
// **             The TDC Number is also encoded in this word.
// **             see ERROR_TDCxxxx
// **   slot      The virtual slot number.
// */
//
//______________________________________________________________________________
void HTCAEN1x90Unpacker::reportError(UInt_t errorWord, int slot)
{
   UInt_t chip = (errorWord & ERROR_TDCMASK) >> ERROR_TDCSHIFT;
   UInt_t errors = errorWord & ERROR_BITS;

   std::cerr << "V1x90: An error word was produced by chip number " << chip << " in vsn " << slot << std::endl;

   std::cerr << "The following error bits were set:\n";
   UInt_t bitnum = 0;
   while (errors) {
      UInt_t bit = 1 << bitnum;
      if (errors & bit) {
         std::cerr << ERROR_STRINGS[bitnum] << std::endl;
         errors &= ~bit;
      }
      bitnum++;
   }
   std::cerr << "-----------------------------------\n";
}

//______________________________________________________________________________
void HTCAEN1x90Unpacker::PrintSummary()
{
   printf("-- module %s --\n", GetName());
   printf("%llu total unpacked data\n", fTotalUnpackedData);
   printf("%llu errors produced\n", fErrorCount);
   printf("%llu VSN mismatches found\n", fVSNMismatchCount);
   printf("%llu TDC data with no hit in reference found\n", fNoReferenceCount);
   printf("\n");
}
ClassImp(HTCAEN1x90Unpacker)
