//
//  RBCCStackUnpacker.h
//
//
//  Created by Andrew Rogers on 3/21/15.
//
//

#ifndef ____RBUSBStack__
#define ____RBUSBStack__

#include <stdio.h>
#include <iostream>

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBTimestamp.h"
#include "RBUSBStackMarker.h"
#include "RBElectronics.h"

#include "TList.h"
#include "TTree.h"
#include <TNamed.h>

using namespace std;

class RBUSBStack :  public RBModuleUnpacker, public RBElectronics
{
private:
  // data structures:
  typedef struct _StackInfo {
    int         s_stackNumber;
    size_t      s_stackSize;
  } StackInfo;

  ULong64_t    fEventCount;
  ULong64_t    fWordsCount;
  ULong64_t    fVsnErrorCount;
  ULong64_t    fBufferMismatchCount;

  RBTimestamp *fUSBTimestamp;  //
  TList       *fStacks;        // Array of stacks.

  TTree       *fChain;        //!

// Utilties:
private:
  static StackInfo assembleEvent(UShort_t* p, std::vector<UShort_t>& event);

public:
  RBUSBStack();
  ~RBUSBStack(){};

  Int_t AddStack();
  Int_t AddToStack(Int_t stackIdx, RBUSBStackMarker *marker);
  Int_t AddToStack(Int_t stackIdx, RBUSBStackMarker *marker, Int_t idx);
  Int_t AddToStack(Int_t stackIdx, RBElectronics *module){AddToStack(stackIdx, -1, module);return 0;}
  Int_t AddToStack(Int_t stackIdx, Int_t geo, RBElectronics *module);
  Int_t AddToStack(Int_t stackIdx, Int_t geo, RBElectronics *module, Int_t idx);
  Int_t RemoveFromStack();

  void  Clear(Option_t *option);

  void  InitClass();
  void  InitBranch(TTree* tree);
  void  InitTree(TTree* tree);
  Int_t Unpack(UShort_t *pEvent, UInt_t offset);

  void  PrintSummary();
  void  AddTTreeUserInfo(TTree *);

  ClassDef(RBUSBStack,1);
};


#endif /* defined(____RBUSBStack__) */
