//
//  RBSisTimestampUnpacker.h
//
// WARNING: This class has been introduced during experiment 15190 to handle
// 2 different timestamps, one for the conventional electronics and another one
// for the Korean electronics (that was under test during e15190)
// For a future experiment this should be taken into account.
//


#ifndef __RBSisTimestampUNPACKER_H
#define __RBSisTimestampUNPACKER_H

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBElectronics.h"

#include "TTree.h"

//#include <stdint.h>

// Based on SpecTcl code written by Kyle Brown, adapted for RIBbit by Juan Manfredi
// Jan 2018

class RBSisTimestampUnpacker : public RBModuleUnpacker, public RBElectronics
{
private:
  ULong64_t fTimestamp;
  ULong64_t fTimestampKoreans;

  TTree               *fChain;                 //! Pointer to current TTree or TChain
  Int_t                fCurrent;               //! Current Tree number in a TChain

public:
  RBSisTimestampUnpacker(const char* chName);
  ~RBSisTimestampUnpacker();

  Int_t   Unpack(std::vector<UShort_t>& event, UInt_t offset);

  //  Int_t   *GetData()        {return fTimes;}

  virtual void InitBranch(TTree* tree);
  virtual void Clear();

  virtual void InitClass(){}
  //  virtual void InitBranch(TTree* tree);
  //  virtual void InitBranch(TTree* tree){}

  virtual void InitTree(TTree* tree){fChain = tree;}

  ULong64_t GetTimestamp(){return fTimestamp;}

  ClassDef(RBSisTimestampUnpacker,1);
};

#endif
