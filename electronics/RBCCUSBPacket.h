//
//  RBCCUSBPacket.h
//  
//
//  Created by Andrew Rogers on 3/20/15.
//
//

#ifndef ____RBCCUSBPacket__
#define ____RBCCUSBPacket__

#include "TObject.h"

/*!
 Defines an interface for unpackers of a specific module unpacker.
 */
//class RBCCUSBPacket : public TObject
class RBCCUSBPacket
{
public:
//  virtual Int_t unpack(UShort_t *pEvent) = 0;
  
protected:
  static Int_t bitsInMask(UShort_t mask);
};

#endif
