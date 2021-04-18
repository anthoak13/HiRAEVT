#ifndef HTROOTCAEN1X90SINGLEHIT_H
#define HTROOTCAEN1X90SINGLEHIT_H

#include "HTRootModule.h"

class HTRootCAEN1x90SingleHit : public HTRootModule {
public:
   Double_t fData[128];
   // Int_t fMaxDepth; // The maximum depth of each channel
   // Short_t fChannelDepth[128]; //Track the depth of each channel to set fEventDepth

   // Double_t *fData[128]; //[fMaxDepth]

   HTRootCAEN1x90SingleHit() : HTRootModule("Undefined") // Default constructor for file reading
   {
   }

   HTRootCAEN1x90SingleHit(TString name);
   ~HTRootCAEN1x90SingleHit();

   virtual void Clear() override;
   void PrintData() override;

   Double_t GetData(Int_t ch);
   void SetData(Int_t ch, Double_t data);

   ClassDefOverride(HTRootCAEN1x90SingleHit, 1)
};

#endif
