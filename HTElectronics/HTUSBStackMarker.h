#ifndef ____HTUSBStackMarker__
#define ____HTUSBStackMarker__

#include "TString.h"

#include "HTElectronics.h"

#include <stdio.h>

using namespace std;

class HTUSBStackMarker : public HTElectronics {

private:
   UShort_t fMarker;
   TString fTitle;

public:
   HTUSBStackMarker(UShort_t marker, const char *title);
   ~HTUSBStackMarker() {}

   UShort_t GetMarker() { return fMarker; }
   TString GetTitle() { return fTitle; }

   void SetTitle(const char *title) { fTitle = title; }

      virtual void InitBranch(TTree *tree) {}
   virtual void InitTree(TTree *tree) {}

   Int_t Unpack(std::vector<UShort_t> &event, Int_t offset);

   ClassDef(HTUSBStackMarker, 1);
};
#endif /* defined(____HTUSBStackMarker__) */
