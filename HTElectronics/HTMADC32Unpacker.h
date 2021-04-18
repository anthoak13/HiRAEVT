//
//  HTMADC32Unpacker.h
//

#ifndef __HTMADC32UNPACKER_H
#define __HTMADC32UNPACKER_H

#include "HTModuleUnpacker.h"

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

/*
 * This unpacker is responsible for unpacking Mesytech 32 channel digitizers.
 * Created by Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 * v1 : 12 February 2019
 */
class HTMADC32Unpacker : public HTModuleUnpacker {
private:
   ULong64_t fTotalUnpackedCount; //!
   ULong64_t fOverflowCount;      //!
   ULong64_t fVSNMismatchCount;   //!

public:
   HTMADC32Unpacker(json moduleDescription);
   ~HTMADC32Unpacker();

   Int_t DecodeVSN(Int_t header) override;
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   void PrintSummary() override;

   ClassDefOverride(HTMADC32Unpacker, 1);
};

#endif
