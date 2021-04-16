#ifndef HTFILTER_H
#define HTFILTER_H

// HTFILTER_H
// Adam Anthony 4/14/2021
// This class just forwards all events to an unpacker class. This is done to get around the
// anoying cloning that the NSCLDAQ does. It is not responsible for managing the memory
// of the passed unpacker.

#include "TString.h"

#include <CFilter.h>
#include <stdint.h>

class CPhysicsEventItem;
class HTUnpacker;

class HTFilter : public CFilter {

private:
   HTUnpacker *fUnpacker;


public:
   HTFilter(HTUnpacker *unpacker);
   ~HTFilter();
   
   virtual HTFilter *clone() const override { return new HTFilter(*this); }

   virtual CRingItem *handleStateChangeItem(CRingStateChangeItem *pItem) override;
   virtual CRingItem *handlePhysicsEventItem(CPhysicsEventItem *pItem) override;

};

#endif
