//
//  HTSisTimestampUnpacker.h
//
// WARNING: This class has been introduced during experiment 15190 to handle
// 2 different timestamps, one for the conventional electronics and another one
// for the Korean electronics (that was under test during e15190)
// For a future experiment this should be taken into account.
//

#ifndef __HTSisTimestampUNPACKER_H
#define __HTSisTimestampUNPACKER_H

#include "HTModuleUnpacker.h"

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

// Based on SpecTcl code written by Kyle Brown, adapted for RIBbit by Juan Manfredi
// Made more general by Adam Anthony Feb 2020

class HTSisTimestampUnpacker : public HTModuleUnpacker {
public:
   HTSisTimestampUnpacker(json moduleDescription);
   ~HTSisTimestampUnpacker();

   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;
   Int_t DecodeVSN(Int_t header) override { return -1; }

   void Print() override { std::cout << "SisTimestamp" << std::endl; }
   void PrintSummary() override;

   ClassDefOverride(HTSisTimestampUnpacker, 1);
};

#endif
