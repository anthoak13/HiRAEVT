#ifndef HTROOTCAEN1X90_H
#define HTROOTCAEN1X90_H

#include "HTRootModule.h"

class HTRootCAEN1x90 : public HTRootModule {
private:
   Int_t fMaxCh;
   std::vector<Double_t> *fData; //[fMaxCh]

public:
   HTRootCAEN1x90() : HTRootModule("Undefined") // Default constructor for file reading
   {
      fData = new std::vector<Double_t>[1];
   }

   HTRootCAEN1x90(TString name, Int_t maxCh);
   ~HTRootCAEN1x90();

   virtual void Clear() override;
   Double_t GetData(Int_t ch, Int_t depth);
   std::vector<Double_t> *GetData(Int_t ch);
   void SetNextData(Int_t ch, Double_t data);
   void SetData(Int_t ch, Int_t depth, Double_t data);

   ClassDefOverride(HTRootCAEN1x90, 1)
};

#endif
