#include "HTModuleUnpacker.h"
#include <iomanip>

ULong_t HTModuleUnpacker::getLong(std::vector<UShort_t> &event, ULong_t offset)
{
   ULong_t low = event[offset];
   ULong_t high = event[offset + 1];
   return low | (high << 16);
}

void HTModuleUnpacker::PrintHex(std::vector<UShort_t> &event, ULong_t offset, ULong_t numbeWords, Int_t wordsPerLine)
{
   for (int i = 0; i < numbeWords; ++i) {
      if (i % wordsPerLine == 0)
         std::cout << std::endl;
      std::cout << std::setfill('0') << std::setw(4) << std::hex << event[offset + i] << " ";
   }
   std::cout << std::endl;
}

ClassImp(HTModuleUnpacker)
