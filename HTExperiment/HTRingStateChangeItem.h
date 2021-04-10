
#ifndef __HTRINGSTATECHANGEITEM_H
#define __HTRINGSTATECHANGEITEM_H

#include "HTRingItem.h"

#include <TBranch.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>
#include <ctime>

using namespace std;

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// HTRingStateChangeItem                                                          //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

class HTRingStateChangeItem : public HTRingItem {

private:
   TString fReason;
   UInt_t fRunNumber;
   UInt_t fTimeOffset;
   time_t fTimestamp;
   TString fRunTitle;

public:
   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

public:
   HTRingStateChangeItem() {}
   HTRingStateChangeItem(ULong64_t eventTimestamp, UInt_t sourceId, UInt_t barrierType, std::string reason,
                         UInt_t runNumber, UInt_t timeOffset, time_t timestamp, std::string title);
   ~HTRingStateChangeItem() {}

   void SetType(std::string reason) { fReason = reason; }

   UInt_t GetRunNumber() { return fRunNumber; }
   TString GetRunTitle() { return fRunTitle; }
   time_t GetTimestamp() { return fTimestamp; }
   const char *GetType() { return fReason.Data(); }

   void Clear(Option_t *option = "");
   void InitClass(); // Calls all InitClass methods.
   void InitTree(TTree *tree);

   ClassDef(HTRingStateChangeItem, 1)
};

#endif
