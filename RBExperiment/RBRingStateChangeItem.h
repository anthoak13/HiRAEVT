
#ifndef __RBRINGSTATECHANGEITEM_H
#define __RBRINGSTATECHANGEITEM_H

#ifndef __ROOTDEFINE_H
#define __ROOTDEFINE_H
#include "rootDefine.h"
#endif

#include <ctime>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

#include "RBRingItem.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////
//                                                                        //
// RBRingStateChangeItem                                                          //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

class RBRingStateChangeItem : public RBRingItem {

 private:
  TString       fReason;
  UInt_t        fRunNumber;
  UInt_t        fTimeOffset;
  time_t        fTimestamp;
  TString       fRunTitle;

 public:

  TTree        *fChain;             //! pointer to the analyzed TTree or TChain
  Int_t         fCurrent;           //! current Tree number in a TChain
  
 public:
  RBRingStateChangeItem() {}
  RBRingStateChangeItem(ULong64_t eventTimestamp, UInt_t sourceId, UInt_t barrierType,
                        std::string reason, UInt_t runNumber, UInt_t timeOffset,
                        time_t timestamp, std::string title);
  ~RBRingStateChangeItem() {}

  void         SetType(std::string reason){fReason = reason;}
  
  UInt_t       GetRunNumber(){return fRunNumber;}
  TString      GetRunTitle() {return fRunTitle;}
  time_t       GetTimestamp(){return fTimestamp;}
  
  void         Clear(Option_t *option="");
  void         InitClass();                                       // Calls all InitClass methods.
  void         InitTree(TTree *tree);
  
  ClassDef(RBRingStateChangeItem,1)

};


#endif
