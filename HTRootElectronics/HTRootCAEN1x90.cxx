#include "HTRootCAEN1x90.h"

#include <iostream>

//________________________________________________
HTRootCAEN1x90::HTRootCAEN1x90(TString name) : HTRootModule(name)
{
   fType = "HTRootCAEN1x90";
   Clear();
}

//________________________________________________
HTRootCAEN1x90::~HTRootCAEN1x90() {}

void HTRootCAEN1x90::Clear()
{
   for (int i = 0; i < 128; ++i)
      fData[i].clear();
}
void HTRootCAEN1x90::PrintData()
{
   for (int i = 0; i < 128; ++i) {
      std::cout << i << ": ";
      for (auto &time : fData[i])
         std::cout << time << " ";
      std::cout << std::endl;
   }
}

std::vector<Double_t> *HTRootCAEN1x90::GetData(Int_t ch)
{
   if (ch < 128)
      return &fData[ch];
   return nullptr;
}

Double_t HTRootCAEN1x90::GetData(Int_t ch, Int_t depth)
{
   if (ch < 128 && depth < fData[ch].size())
      return fData[ch][depth];
   else
      return -9999;
}

void HTRootCAEN1x90::SetData(Int_t ch, Int_t depth, Double_t data)
{
   if (ch < 128) {
      while (fData[ch].size() < depth)
         fData[ch].push_back(-9999);
      fData[ch].push_back(data);
   }
}
void HTRootCAEN1x90::SetNextData(Int_t ch, Double_t data)
{
   if (ch < 128)
      fData[ch].push_back(data);
}
ClassImp(HTRootCAEN1x90)
