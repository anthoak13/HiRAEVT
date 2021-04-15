#include "HTRootCAEN1x90.h"
#include <iostream>


//________________________________________________
HTRootCAEN1x90::HTRootCAEN1x90(TString name, Int_t maxCh)
   : HTRootModule(name), fMaxCh(maxCh)
{

   fData = new std::vector<Double_t>[fMaxCh];
//   for(int i = 0; i < fMaxCh; ++i)
//      fData.push_back(std::vector<Double_t>());
}

//________________________________________________
HTRootCAEN1x90::~HTRootCAEN1x90()
{
   std::cout << "Deconstructing: " << fName << std::endl;
}

void HTRootCAEN1x90::Clear()
{
   for( int i =0;i<fMaxCh;++i)
      fData[i].clear();
}

Double_t HTRootCAEN1x90::GetData(Int_t ch, Int_t depth)
{
   if(ch < fMaxCh && fData[ch].size() > depth)
      return fData[ch].at(depth);
   else
      return -9999;
}

std::vector<Double_t> *HTRootCAEN1x90::GetData(Int_t ch)
{
   if (ch < fMaxCh)
      return &fData[ch];
   else
      return nullptr;
}

void HTRootCAEN1x90::SetData(Int_t ch, Int_t depth, Double_t data)
{
   if(ch < fMaxCh)
   {
      while(fData[ch].size() <= depth)
	 fData[ch].push_back(-9999.);
      fData[ch][depth] = data;
   }
}

void HTRootCAEN1x90::SetNextData(Int_t ch, Double_t data)
{
   if(ch < fMaxCh)
      fData[ch].push_back(data);
}

ClassImp(HTRootCAEN1x90)
