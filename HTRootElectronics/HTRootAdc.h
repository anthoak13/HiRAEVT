#ifndef HTROOTADC_H
#define HTROOTADC_H

#include "HTRootModule.h"

class HTRootAdc : public HTRootModule {
private:
   Int_t fMaxCh;
   Short_t *fData; //[fMaxCh] 

public:
   HTRootAdc(TString name, Int_t maxCh = 32);
   ~HTRootAdc();

   Short_t GetData(int) const;

   ClassDef(HTRootAdc,1)


};

#endif
