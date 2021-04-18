//
//  HTSisTimestampUnpacker.cpp
//

#include "HTSisTimestampUnpacker.h"

#include "HTRootSisTimestamp.h"

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

HTSisTimestampUnpacker::HTSisTimestampUnpacker(json moduleDescription)
{
   TString name = moduleDescription["moduleName"].get<std::string>();

   fModule = new HTRootSisTimestamp(name);
}
HTSisTimestampUnpacker::~HTSisTimestampUnpacker() {}

Int_t HTSisTimestampUnpacker::Unpack(std::vector<UShort_t> &event, UInt_t offset)
{
   auto ptrMod = dynamic_cast<HTRootSisTimestamp *>(fModule);
   ptrMod->Clear();
   // Print out what's being unpacked
   // std::cout << "HTSistimestampunpacker: " << std::endl;
   // PrintHex(event, offset, 6);

   uint64_t low0 = event[offset];
   uint64_t mid0 = event[offset + 1];
   uint64_t low1 = event[offset + 2];
   uint64_t mid1 = event[offset + 3];
   uint64_t high0 = event[offset + 4];
   uint64_t high1 = event[offset + 5];
   offset += 6;

   ptrMod->SetData(0, low0 | (mid0 << 16) | (high0 << 32));
   ptrMod->SetData(1, low1 | (mid1 << 16) | (high1 << 32));

   return offset;
}

void HTSisTimestampUnpacker::PrintSummary()
{
   std::cout << "-- module " << GetName() << " --" << std::endl << std::endl;
}

ClassImp(HTSisTimestampUnpacker)
