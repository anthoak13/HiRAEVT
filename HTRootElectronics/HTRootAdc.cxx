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

ClassImp(HTRootAdc)
