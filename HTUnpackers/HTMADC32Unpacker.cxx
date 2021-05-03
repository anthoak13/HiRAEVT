//
//  HTMADC32Unpacker.cpp
//

#include "HTMADC32Unpacker.h"

// Constants

// All longwords have a type in the top two bits:

static const uint32_t ALL_TYPEMASK(0xc0000000);
static const uint32_t ALL_TYPESHFT(30);

static const uint32_t TYPE_HEADER(1);
static const uint32_t TYPE_DATA(0);
static const uint32_t TYPE_TRAILER(3);

// Fields in the headers:

static const uint32_t HDR_COUNTMASK(0x7ff);

static const uint32_t HDR_ERRORMASK(0x800); // Buffer overflow.
static const uint32_t HDR_ERRORSHFT(12);

static const uint32_t HDR_IDMASK(0xff0000);
static const uint32_t HDR_IDSHFT(16);

// Fields in the data words:

static const uint32_t DATA_VALUEMASK(0x1fff);

static const uint32_t DATA_ISOVERFLOW(0x4000);

static const uint32_t DATA_CHANNELMASK(0x1f0000);
static const uint32_t DATA_CHANNELSHFT(16);

static const uint32_t DATA_ISPAD(0x04000000);

// Fields in the trailer.

static const uint32_t TRAILER_COUNTMASK(0x3fffffff); // trigger count or timestamp counter.

#include "HTRootAdc.h"

#include <iostream>

#include "nlohmann/json.hpp"

using namespace std;

//______________________________________________________________________________
HTMADC32Unpacker::HTMADC32Unpacker(json moduleDescription)
   : fTotalUnpackedCount(0), fOverflowCount(0), fVSNMismatchCount(0)
{
   TString name = moduleDescription["moduleName"].get<std::string>();
   Int_t vsn = moduleDescription["vsn"].get<int>();

   SetVSN(vsn);
   fModule = new HTRootAdc(name);
}

//______________________________________________________________________________
HTMADC32Unpacker::~HTMADC32Unpacker() {}

//////////////////////////////////////////////////////////////////////
//  Virtual function overrides

/*!
 Perform the unpack.
 - If we are not pointing to the header corresopnding to our ADC,
 skip out without doing anything.
 - For all data words, until we see a non data word;
 extract the data -> the parameter index indicated by our parameter map.

 \param event   - References the vector containing the assembled event
 (the internal segment headers have been removed).
 \param offset  - Index in event to our chunk.

 \return unsigned int
 \retval offset to the first word of the event not processed by this member.

 \note - Overflow and Underflow parameters are not transferred to parameters.
 \note - the data are in little-endian form.
 */
//______________________________________________________________________________
Int_t HTMADC32Unpacker::Unpack(vector<UShort_t> &event, UInt_t offset)
{
   // the correct pointer to the module
   auto modPtr = dynamic_cast<HTRootAdc *>(fModule);
   modPtr->Clear();

   auto origOffset = offset;

   // Get the 'header' .. ensure that it is one and that it matches our VSN.
   unsigned long header = getLong(event, offset);
   if (header == 0xffffffff) { // ADC had no data there will be just the two words of 0xffffffff
      return offset + 2;
   }

   uint32_t type = (header & ALL_TYPEMASK) >> ALL_TYPESHFT;
   if (type != TYPE_HEADER)
      return offset;

   int longsRead = 1; // Count the longwords processed:

   int id = DecodeVSN(header);

   if (id != GetVSN()) {
      std::cout << "VSN mismatch: " << id << " " << GetVSN() << std::endl;
      fVSNMismatchCount++;
      return offset;
   }

   // If we do not have a VSN and all we have are 0xffff's then return.
   if (GetVSN() == -1 && event[offset] == 0xffff && event[offset + 1] == 0xffff)
      return offset + 2;

   // Ok this is our data:
   // We're going to use the trailer to terminate so we don't need the
   // conversion count field of the header.

   offset += 2; // Next longword..

   // Overflow bin is set to 9999 by Daniele Dell'Aquila (2019 Feb 13th)

   unsigned long datum = getLong(event, offset);
   longsRead++;
   offset += 2;

   // Loop through data until we hit something that is not dataOA
   while (((datum & ALL_TYPEMASK) >> ALL_TYPESHFT) == TYPE_DATA) {

      bool overflow = (datum & DATA_ISOVERFLOW) != 0;
      if (!overflow) {
         int channel = (datum & DATA_CHANNELMASK) >> DATA_CHANNELSHFT;
         int value = datum & DATA_VALUEMASK;
         modPtr->SetData(channel, value);
      } else {
         fOverflowCount++;
         int channel = (datum & DATA_CHANNELMASK) >> DATA_CHANNELSHFT;
         int value = 9999;
         modPtr->SetData(channel, value);
      }
      datum = getLong(event, offset);
      longsRead++;
      offset += 2;
   }
   // The datum should be the trailer.. verify this..

   if (((datum & ALL_TYPEMASK) >> ALL_TYPESHFT) != TYPE_TRAILER) {
      longsRead--; // Really should not happen!!
   }

   fTotalUnpackedCount += longsRead;

   // There will be a 0xffffffff longword for the BERR at the end of the
   // readout.

   // std::cout << "HTMADC32Unpacker: " <<std::endl;
   // PrintHex(event, origOffset, offset-origOffset);

   return offset + 2;
}

//______________________________________________________________________________
Int_t HTMADC32Unpacker::DecodeVSN(Int_t header)
{
   // --
   //
   return ((header & HDR_IDMASK) >> HDR_IDSHFT);
}

//______________________________________________________________________________
void HTMADC32Unpacker::PrintSummary()
{
   printf("-- module %s --\n", fModule->GetName());
   printf("%llu total unpacked data\n", fTotalUnpackedCount);
   printf("%llu VSN mismatches found\n", fVSNMismatchCount);
   printf("%.1f %% overflows data\n", 100 * double(fOverflowCount) / double(fTotalUnpackedCount));
   printf("\n");
}

ClassImp(HTMADC32Unpacker)
