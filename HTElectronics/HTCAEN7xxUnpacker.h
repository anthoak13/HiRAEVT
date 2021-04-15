//
//  HTCAEN7xxUnpacker.h
//

#ifndef __HTCAEN7xxUNPACKER_H
#define __HTCAEN7xxUNPACKER_H

#include "HTModuleUnpacker.h"

/*!
 This unpacker is responsible for unpacking CAEN 32 channel digitizers.  These modules
 include the CAEN V775, 785, 792, and 862 modules.  These modules have a
 virtual slot number.  Furthermore it is possible that the readout of a specific
 module may be completely supressed.  Fortunately the header of a module is
 quite unambiguous and this unpacker can deal with that case just fine.
 */
class HTCAEN7xxUnpacker : public HTModuleUnpacker {
private:
   ULong64_t fTotalUnpackedCount; //!
   ULong64_t fOverflowCount;      //!
   ULong64_t fVSNMismatchCount;   //!

public:
   HTCAEN7xxUnpacker(TString name);
   ~HTCAEN7xxUnpacker();

   Int_t DecodeVSN(Int_t header) override;
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   void PrintSummary() override;

   ClassDefOverride(HTCAEN7xxUnpacker, 1);
};

#endif
