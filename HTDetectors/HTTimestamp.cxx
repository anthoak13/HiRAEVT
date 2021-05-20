#include "HTTimestamp.h"

#include "nlohmann/json.hpp"

HTTimestamp::HTTimestamp(const TString detectorName) : HTDetector(detectorName)
{
   fType = "HTTimestamp";
   Clear();
}


void HTTimestamp::Clear()
{
   fTimestamp = 0;
}

void HTTimestamp::Calibrate(const json &cal) {}

ClassImp(HTTimestamp);
