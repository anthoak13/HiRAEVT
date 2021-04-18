#include "HTFilter.h"

#include "HTUnpacker.h"

#include <CFilter.h>
#include <CPhysicsEventItem.h>
#include <CRingStateChangeItem.h>

HTFilter::HTFilter(HTUnpacker *unpacker) : fUnpacker(unpacker) {}

HTFilter::~HTFilter() {}
// handle the state change events
CRingItem *HTFilter::handleStateChangeItem(CRingStateChangeItem *pItem)
{
   return fUnpacker->handleStateChangeItem(pItem);
}

// handle the physics events
CRingItem *HTFilter::handlePhysicsEventItem(CPhysicsEventItem *pItem)
{
   return fUnpacker->handlePhysicsEventItem(pItem);
}
