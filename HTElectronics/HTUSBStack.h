//
//  HTCCStackUnpacker.h
//
//
//  Created by Andrew Rogers on 3/21/15.
//
//

#ifndef ____HTUSBStack__
#define ____HTUSBStack__

#include "TList.h"
#include "TTree.h"

#include <TNamed.h>
#include <iostream>
#include <stdio.h>

class HTModuleUnpacker;

using namespace std;

class HTUSBStack {
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

   TList *fStacks;             // Array of stacks.

   TTree *fChain; //!

   // Utilties:
private:
   static StackInfo assembleEvent(UShort_t *p, std::vector<UShort_t> &event);
   static ULong_t getLong(std::vector<UShort_t> &event, ULong_t offset);

public:
   HTUSBStack();
   ~HTUSBStack(){};

   Int_t AddStack();
   Int_t AddToStack(Int_t stackIdx, HTModuleUnpacker *module)
   {
      AddToStack(stackIdx, -1, module);
      return 0;
   }
   Int_t AddToStack(Int_t stackIdx, Int_t geo, HTModuleUnpacker *module);
   Int_t AddToStack(Int_t stackIdx, Int_t geo, HTModuleUnpacker *module, Int_t idx);
   Int_t RemoveFromStack();

   Int_t Unpack(UShort_t *pEvent, UInt_t offset);

   ClassDef(HTUSBStack, 1);
};

#endif /* defined(____HTUSBStack__) */
