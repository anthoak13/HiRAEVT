// Implementation of the non-pure members of the module unpacker.

//#include <config.h>
#include "RBModuleUnpacker.h"

#include <stdio.h>


RBModuleUnpacker::~RBModuleUnpacker()
{}



// unpack a longword from the event array...assumption is that localhost is
// little endian.

unsigned long
RBModuleUnpacker::getLong(std::vector<unsigned short>& event,
                          unsigned int offset)
{
  printf("mi trovo dentro get long\n");
  printf("offset = %u\n",offset);
  
  unsigned long low = event[offset];
  unsigned long hi  = event[offset+1];
  
  printf("low = %lu\thi=%lu\n",low,hi);
  
  return low | (hi << 16);
}
