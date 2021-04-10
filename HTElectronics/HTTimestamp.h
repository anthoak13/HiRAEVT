#ifndef ____HTTimestamp__
#define ____HTTimestamp__

#include "TTree.h"

#include "HTElectronics.h"

#include <stdio.h>

using namespace std;

class HTTimestamp : public HTElectronics {

private:
   ULong64_t fTimestamp; // Timestamp value.

   TTree *fChain; //!

public:
   TBranch *b_fTimestamp;

public:
   HTTimestamp(const char *bName);
   ~HTTimestamp() {}

   ULong64_t GetTimestamp() { return fTimestamp; }

   virtual void Clear(Option_t *option = "");

   virtual void InitClass() {}
   virtual void InitBranch(TTree *tree);
   virtual void InitTree(TTree *tree) { fChain = tree; }

   Int_t Unpack(UShort_t *pEvent);

   ClassDef(HTTimestamp, 1);
};
#endif /* defined(____HTTimestamp__) */
