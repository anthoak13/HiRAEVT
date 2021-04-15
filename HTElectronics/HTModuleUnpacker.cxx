#include "HTModuleUnpacker.h"

ULong_t HTModuleUnpacker::getLong(std::vector<UShort_t> &event, ULong_t offset)
{
   ULong_t low = event[offset];
   ULong_t high = event[offset + 1];
   return low | (high << 16);
}

ClassImp(HTModuleUnpacker)
