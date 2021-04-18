#include "HTExperimentInfo.h"

HTExperimentInfo::HTExperimentInfo(Int_t expNumber) : fExperimentNumber(expNumber)
{
   fName.Form("E%dInfo", fExperimentNumber);
}
ClassImp(HTExperimentInfo);
