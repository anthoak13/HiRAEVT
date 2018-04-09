#ifndef ____RBUSBStackMarker__
#define ____RBUSBStackMarker__

#include <stdio.h>

#include "TString.h"

#include "RBElectronics.h"

using namespace std;

class RBUSBStackMarker : public RBElectronics{

private:
  UShort_t     fMarker;
  TString      fTitle;
  
public:
  RBUSBStackMarker(UShort_t marker, const char *title);
  ~RBUSBStackMarker(){}
  
  UShort_t GetMarker(){return fMarker;}
  TString  GetTitle() {return fTitle;}
  
  void     SetTitle(const char *title){fTitle = title;}
  
  virtual void  InitClass()            {}
  virtual void  InitBranch(TTree* tree){}
  virtual void  InitTree(TTree* tree)  {}
  
  Int_t  Unpack(std::vector<UShort_t>& event, Int_t offset);
  
  ClassDef(RBUSBStackMarker,1);
};
#endif /* defined(____RBUSBStackMarker__) */
