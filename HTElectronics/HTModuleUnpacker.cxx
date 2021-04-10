// Implementation of the non-pure members of the module unpacker.

//#include <config.h>
#include "HTModuleUnpacker.h"

HTModuleUnpacker::~HTModuleUnpacker() {}

// unpack a longword from the event array...assumption is that localhost is
// little endian.

unsigned long HTModuleUnpacker::getLong(std::vector<unsigned short> &event, unsigned int offset)
{
   unsigned long low = event[offset];
   unsigned long hi = event[offset + 1];

   return low | (hi << 16);
}
