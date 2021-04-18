#include "HTRootAdc.h"

#include <iostream>

//________________________________________________
HTRootAdc::HTRootAdc(TString name) : HTRootModule(name)
{
   fType = "HTRootAdc";
   Clear();
}

//________________________________________________
HTRootAdc::~HTRootAdc() {}

void HTRootAdc::Clear()
{
   for (int i = 0; i < 32; ++i)
      fData[i] = -9999;
}
void HTRootAdc::PrintData()
{
   std::cout << fName << std::endl;
   for (int i = 0; i < 32; ++i)
      std::cout << i << " " << fData[i] << std::endl;
}

Short_t HTRootAdc::GetData(Int_t ch) const
{
   return ch < 32 ? fData[ch] : -9999;
}

void HTRootAdc::SetData(Int_t ch, Short_t data)
{
   if (ch < 32)
      fData[ch] = data;
}
ClassImp(HTRootAdc)
