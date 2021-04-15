//
//  HTSisTimestampUnpacker.cpp
//


#include "HTSisTimestampUnpacker.h"
#include "HTRootSisTimestamp.h"

using namespace std;

ClassImp(HTSisTimestampUnpacker)

HTSisTimestampUnpacker::HTSisTimestampUnpacker(TString name)
{
   fModule = std::make_shared<HTRootSisTimestamp>(name);
}
HTSisTimestampUnpacker::~HTSisTimestampUnpacker() {}


Int_t HTSisTimestampUnpacker::Unpack(vector<UShort_t> &event, UInt_t offset)
{
   Clear();

   uint64_t low0 = event[offset];
   uint64_t mid0 = event[offset + 1];
   uint64_t low1 = event[offset + 2];
   uint64_t mid1 = event[offset + 3];
   uint64_t high0 = event[offset + 4];
   uint64_t high1 = event[offset + 5];
   offset += 6;

   auto ptrMod = dynamic_pointer_cast<HTRootSisTimestamp>(fModule);
   ptrMod.get()->SetData(0, low0 | (mid0 << 16) | (high0 << 32));
   ptrMod.get()->SetData(1, low1 | (mid1 << 16) | (high1 << 32));
   
   return offset;
}
