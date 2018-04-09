
#ifndef __RBRINGITEM_H
#define __RBRINGITEM_H

#ifndef __ROOTDEFINE_H
#define __ROOTDEFINE_H
#include "rootDefine.h"
#endif

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

using namespace std;


////////////////////////////////////////////////////////////////////////////
//                                                                        //
// RBRingItem                                                          //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

class RBRingItem : public TObject {

 protected:
  UShort_t  fType;                   //
  ULong64_t fTimestamp;              //
  UInt_t    fSourceId;               //
  UInt_t    fBarrierType;            //
  size_t    fMaxBody;                //

 public:
  TBranch      *b_Type;             //! type branch.
  TBranch      *b_Timestamp;        //!
  TBranch      *b_SourceId;         //!
  TBranch      *b_BarrierType;      //!
  TBranch      *b_MaxBody;          //!

  TTree        *fChain;             //! pointer to the analyzed TTree or TChain
  Int_t         fCurrent;           //! current Tree number in a TChain
  
 public:
  RBRingItem() {}
  RBRingItem(UShort_t type, ULong64_t timestamp, UInt_t sourceId,
             UInt_t barrierType = 0, size_t  maxBody = 8192);
  ~RBRingItem() {}

  void         SetType(UShort_t type){fType = type;}
  void         SetBodyHeader(ULong64_t timestamp, UInt_t sourceId,
                             UInt_t barrierType = 0);
  virtual void Clear(Option_t *option="");
  virtual void InitClass();                                       // Calls all InitClass methods.
  virtual void InitTree(TTree *tree);
  
  ClassDef(RBRingItem,1)

};


#endif
