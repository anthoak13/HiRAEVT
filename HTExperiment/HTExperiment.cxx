
#include "HTExperiment.h"

HTExperiment::HTExperiment() : fName("HTExperiment") {}

HTExperiment::HTExperiment(Int_t expNumber)
{
   fName.Form("E%d", expNumber);
}

ClassImp(HTExperiment); // NSCL event-data unpacker.
