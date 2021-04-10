
#include <TEventList.h>
#include <TFile.h>
#include <TTree.h>
#include <stdio.h>

// #ifndef __HTRingItem_H
// #define __HTRingItem_H
#include "HTRingItem.h"
//#endif

ClassImp(HTRingItem);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML

END_HTML */
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
HTRingItem::HTRingItem(UShort_t type, ULong64_t timestamp, UInt_t sourceId, UInt_t barrierType, size_t maxBody)
{
   SetType(type);
   SetBodyHeader(timestamp, sourceId, barrierType);
}

//______________________________________________________________________________
void HTRingItem::SetBodyHeader(ULong64_t timestamp, UInt_t sourceId, UInt_t barrierType)
{
   fTimestamp = timestamp;
   fSourceId = sourceId;
   fBarrierType = barrierType;
}

//______________________________________________________________________________
void HTRingItem::Clear(Option_t *)
{
   // -- Clear the data members
   //
}

//______________________________________________________________________________
void HTRingItem::InitClass()
{
   // -- Initialize the class to its default settings.
   //

   Clear();
}

//______________________________________________________________________________
void HTRingItem::InitTree(TTree *tree)
{
   // -- Set the branch pointers.
   //

   fChain = tree;
   fCurrent = -1;
}
