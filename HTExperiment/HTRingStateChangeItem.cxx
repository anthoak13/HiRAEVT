
#include <TEventList.h>
#include <TFile.h>
#include <TTree.h>
#include <stdio.h>

// #ifndef __HTRingStateChangeItem_H
// #define __HTRingStateChangeItem_H
#include "HTRingStateChangeItem.h"
//#endif

ClassImp(HTRingStateChangeItem);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML

END_HTML */
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
HTRingStateChangeItem::HTRingStateChangeItem(ULong64_t eventTimestamp, UInt_t sourceId, UInt_t barrierType,
                                             std::string reason, UInt_t runNumber, UInt_t timeOffset, time_t timestamp,
                                             std::string title)
{
   SetType(reason);
   SetBodyHeader(eventTimestamp, sourceId, barrierType);
   fRunNumber = runNumber;
   fTimeOffset = timeOffset;
   fTimestamp = timestamp;
   fRunTitle = title;
}

//______________________________________________________________________________
void HTRingStateChangeItem::Clear(Option_t *)
{
   // -- Clear the data members
   //
}

//______________________________________________________________________________
void HTRingStateChangeItem::InitClass()
{
   // -- Initialize the class to its default settings.
   //

   Clear();
}

//______________________________________________________________________________
void HTRingStateChangeItem::InitTree(TTree *tree)
{
   // -- Set the branch pointers.
   //

   fChain = tree;
   fCurrent = -1;
}
