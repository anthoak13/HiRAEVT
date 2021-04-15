#ifndef HTROOTCAEN1X90_H
#define HTROOTCAEN1X90_H

#include "HTRootModule.h"


class HTRootCAEN1x90 : public HTRootModule {
private:
   Int_t fMaxCh;
   Double_t *fData;   //[fMaxCh] The data
   
public:
   HTRootCAEN1x90(TString name, Int_t maxCh);
   ~HTRootCAEN1x90();

   Double_t GetData(Int_t ch) { return ch < fMaxCh ? fData[ch] : -9999.; }
   void SetData(Int_t ch, Double_t data) { if ( ch < fMaxCh) fData[ch] = data;}

   ClassDef(HTRootCAEN1x90, 1)

};

#endif
