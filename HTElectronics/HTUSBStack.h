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

#include "TList.h"
#include "TTree.h"

#include "HTElectronics.h"
#include "HTUSBStackMarker.h"

#include <TNamed.h>

using namespace std;

class HTUSBStack : public HTElectronics {
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

   void Clear(Option_t *option)override;

   void InitClass()override;
   void InitBranch(TTree *tree)override;
   void InitTree(TTree *tree)override;
   Int_t Unpack(UShort_t *pEvent, UInt_t offset);
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override { return -1;}


   Short_t GetData(Int_t ch) override { return -1;}
   Double_t GetDataf(Int_t ch) override { return -1;}
   
   void PrintSummary()override;
   void Print() override { std::cout << "HTUSBstack" << std::endl; }
   void AddTTreeUserInfo(TTree *) override;

   ClassDefOverride(HTUSBStack, 1);
};

#endif /* defined(____HTUSBStack__) */
