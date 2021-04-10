//
//  HTCCStackUnpacker.h
//
//
//  Created by Andrew Rogers on 3/21/15.
//
//

#ifndef ____HTUSBStack__
#define ____HTUSBStack__

#include <iostream>
#include <stdio.h>

#ifndef __HTMODULEUNPACKER_H
#include "HTModuleUnpacker.h"
#endif

#include "TList.h"
#include "TTree.h"

#include "HTElectronics.h"
#include "HTTimestamp.h"
#include "HTUSBStackMarker.h"

#include <TNamed.h>

using namespace std;

class HTUSBStack : public HTModuleUnpacker, public HTElectronics {
private:
   // data structures:
   typedef struct _StackInfo {
      int s_stackNumber;
      size_t s_stackSize;
   } StackInfo;

   ULong64_t fEventCount;
   ULong64_t fWordsCount;
   ULong64_t fVsnErrorCount;
   ULong64_t fBufferMismatchCount;

   HTTimestamp *fUSBTimestamp; //
   TList *fStacks;             // Array of stacks.

   TTree *fChain; //!

   // Utilties:
private:
   static StackInfo assembleEvent(UShort_t *p, std::vector<UShort_t> &event);

public:
   HTUSBStack();
   ~HTUSBStack(){};

   Int_t AddStack();
   Int_t AddToStack(Int_t stackIdx, HTUSBStackMarker *marker);
   Int_t AddToStack(Int_t stackIdx, HTUSBStackMarker *marker, Int_t idx);
   Int_t AddToStack(Int_t stackIdx, HTElectronics *module)
   {
      AddToStack(stackIdx, -1, module);
      return 0;
   }
   Int_t AddToStack(Int_t stackIdx, Int_t geo, HTElectronics *module);
   Int_t AddToStack(Int_t stackIdx, Int_t geo, HTElectronics *module, Int_t idx);
   Int_t RemoveFromStack();

   void Clear(Option_t *option);

   void InitClass();
   void InitBranch(TTree *tree);
   void InitTree(TTree *tree);
   Int_t Unpack(UShort_t *pEvent, UInt_t offset);

   void PrintSummary();
   void Print() override { std::cout << "HTUSBstack" << std::endl; }
   void AddTTreeUserInfo(TTree *);

   ClassDef(HTUSBStack, 1);
};

#endif /* defined(____HTUSBStack__) */
