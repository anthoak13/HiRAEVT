#include "HTRootCAEN1x90SingleHit.h"

#include <iostream>

//________________________________________________
HTRootCAEN1x90SingleHit::HTRootCAEN1x90SingleHit(TString name) : HTRootModule(name)
{
   fType = "HTRootCAEN1x90SingleHit";

   Clear();
}

//________________________________________________
HTRootCAEN1x90SingleHit::~HTRootCAEN1x90SingleHit() {}

void HTRootCAEN1x90SingleHit::Clear()
{
   for (int i = 0; i < 128; ++i)
      fData[i] = -9999;
}
void HTRootCAEN1x90SingleHit::PrintData()
{
   for (int i = 0; i < 128; ++i)
      std::cout << i << ": " << fData[i] << std::endl;
}

Double_t HTRootCAEN1x90SingleHit::GetData(Int_t ch)
{
   if (ch < 128)
      return fData[ch];
   return -9999;
}

void HTRootCAEN1x90SingleHit::SetData(Int_t ch, Double_t data)
{
   if (ch < 128)
      fData[ch] = data;
}

ClassImp(HTRootCAEN1x90SingleHit)
