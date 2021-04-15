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

   virtual void Clear() override;
   Short_t GetData(Int_t ch) const;
   void SetData(Int_t ch, Short_t data);

   ClassDefOverride(HTRootAdc, 1)
};

#endif
