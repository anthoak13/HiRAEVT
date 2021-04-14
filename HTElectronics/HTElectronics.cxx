//
//  HTElectronics.cpp
//
//
//  Created by Andrew Rogers on 3/20/15.
//
//

#include "HTElectronics.h"

ULong_t HTElectronics::getLong(std::vector<UShort_t> &event, ULong_t offset)
{
   ULong_t low = event[offset];
   ULong_t hi = event[offset + 1];

   return low | (hi << 16);
}
ClassImp(HTElectronics);
