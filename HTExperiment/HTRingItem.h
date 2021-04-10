
#ifndef __HTRINGITEM_H
#define __HTRINGITEM_H

#include <TBranch.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// HTRingItem                                                          //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

class HTRingItem : public TObject {

protected:
   UShort_t fType;       //
   ULong64_t fTimestamp; //
   UInt_t fSourceId;     //
   UInt_t fBarrierType;  //
   size_t fMaxBody;      //

public:
   TBranch *b_Type;        //! type branch.
   TBranch *b_Timestamp;   //!
   TBranch *b_SourceId;    //!
   TBranch *b_BarrierType; //!
   TBranch *b_MaxBody;     //!

   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

public:
   HTRingItem() {}
   HTRingItem(UShort_t type, ULong64_t timestamp, UInt_t sourceId, UInt_t barrierType = 0, size_t maxBody = 8192);
   ~HTRingItem() {}

   void SetType(UShort_t type) { fType = type; }
   void SetBodyHeader(ULong64_t timestamp, UInt_t sourceId, UInt_t barrierType = 0);
   virtual void Clear(Option_t *option = "");
   virtual void InitClass(); // Calls all InitClass methods.
   virtual void InitTree(TTree *tree);

   ClassDef(HTRingItem, 1)
};

#endif
