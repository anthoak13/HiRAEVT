
#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TEventList.h>

// #ifndef __RBRingItem_H
// #define __RBRingItem_H
#include "RBRingItem.h"
  //#endif


ClassImp(RBRingItem);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML

END_HTML */
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
RBRingItem::RBRingItem(UShort_t type, ULong64_t timestamp, UInt_t sourceId,
                       UInt_t barrierType, size_t  maxBody)
{
  SetType(type);
  SetBodyHeader(timestamp, sourceId, barrierType);
}


//______________________________________________________________________________
void RBRingItem::SetBodyHeader(ULong64_t timestamp, UInt_t sourceId,
                               UInt_t barrierType)
{
  fTimestamp   = timestamp;
  fSourceId    = sourceId;
  fBarrierType = barrierType;
}


//______________________________________________________________________________
void RBRingItem::Clear(Option_t *)
{
  // -- Clear the data members
  //

}


//______________________________________________________________________________
void RBRingItem::InitClass()
{
  // -- Initialize the class to its default settings.
  //

  Clear();
}


//______________________________________________________________________________
void RBRingItem::InitTree(TTree *tree)
{
  // -- Set the branch pointers.
  //

  fChain = tree;
  fCurrent = -1;

}
