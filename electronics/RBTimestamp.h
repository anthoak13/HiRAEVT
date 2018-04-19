#ifndef ____RBTimestamp__
#define ____RBTimestamp__

#include <stdio.h>

#include "TTree.h"

#include "RBElectronics.h"

using namespace std;

class RBTimestamp : public RBElectronics{

private:
  ULong64_t    fTimestamp;        // Timestamp value.

  TTree       *fChain;            //!

public:
  TBranch     *b_fTimestamp;

public:
  RBTimestamp(const char *bName);
  ~RBTimestamp(){}

  ULong64_t     GetTimestamp(){return fTimestamp;}

  virtual void  Clear(Option_t *option="");

  virtual void  InitClass(){}
  virtual void  InitBranch(TTree* tree);
  virtual void  InitTree(TTree* tree){fChain = tree;}

  Int_t Unpack(UShort_t *pEvent);

  ClassDef(RBTimestamp,1);
};
#endif /* defined(____RBTimestamp__) */
