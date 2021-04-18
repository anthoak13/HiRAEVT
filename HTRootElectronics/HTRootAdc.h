#ifndef HTROOTADC_H
#define HTROOTADC_H

#include "HTRootModule.h"

class HTRootAdc : public HTRootModule {
public:
   Short_t fData[32];

   HTRootAdc() : HTRootModule("Undefined") {}
   HTRootAdc(TString name);
   ~HTRootAdc();

   virtual void Clear() override;
   void PrintData() override;
   Short_t GetData(Int_t ch) const;
   void SetData(Int_t ch, Short_t data);

   ClassDefOverride(HTRootAdc, 1)
};

#endif
