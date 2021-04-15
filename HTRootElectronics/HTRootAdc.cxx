#include "HTRootAdc.h"

//________________________________________________
HTRootAdc::HTRootAdc(TString name, Int_t maxCh)
   : HTRootModule(name), fMaxCh(maxCh)
{
   fData = new Short_t[fMaxCh];
}

//________________________________________________
HTRootAdc::~HTRootAdc()
{
   if (fData)
      delete[] fData;
}

void HTRootAdc::Clear()
{
   for(int i = 0; i < fMaxCh; ++i)
      fData[i] = -9999;
}

Short_t HTRootAdc::GetData(Int_t ch) const
{
   return ch < fMaxCh ? fData[ch] : -9999;
}

void HTRootAdc::SetData(Int_t ch, Short_t data)
{
   if(ch<fMaxCh)
      fData[ch] = data;
}
ClassImp(HTRootAdc)
