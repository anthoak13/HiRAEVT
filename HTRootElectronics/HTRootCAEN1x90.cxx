#include "HTRootCAEN1x90.h"

//________________________________________________
HTRootCAEN1x90::HTRootCAEN1x90(TString name, Int_t maxCh) : HTRootModule(name), fMaxCh(maxCh)
{
   fData = new Double_t[maxCh];
}

//________________________________________________
HTRootCAEN1x90::~HTRootCAEN1x90()
{
   if (fData)
      delete[] fData;
}

ClassImp(HTRootCAEN1x90)
