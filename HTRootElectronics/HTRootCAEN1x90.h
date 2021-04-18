#ifndef HTROOTCAEN1X90_H
#define HTROOTCAEN1X90_H

#include "HTRootModule.h"

class HTRootCAEN1x90 : public HTRootModule {
public:
   std::vector<Double_t> fData[128];

   HTRootCAEN1x90() : HTRootModule("Undefined") // Default constructor for file reading
   {
   }

   HTRootCAEN1x90(TString name);
   ~HTRootCAEN1x90();

   virtual void Clear() override;
   void PrintData() override;

   Double_t GetData(Int_t ch, Int_t depth);
   std::vector<Double_t> *GetData(Int_t ch);
   // Double_t *GetData(Int_t ch);
   void SetNextData(Int_t ch, Double_t data);
   void SetData(Int_t ch, Int_t depth, Double_t data);

   ClassDefOverride(HTRootCAEN1x90, 2)
};

#endif
