// Implementation of SimpleDetector

#include "HTSimpleDetector.h"

#include "HTCalibrator.h"

#include "nlohmann/json.hpp"

HTSimpleDetector::HTSimpleDetector(const TString detectorName) : HTDetector(detectorName)
{
   fType = "HTSimpleDetector";

   Clear();
}

HTSimpleDetector::~HTSimpleDetector() {}

void HTSimpleDetector::SetEnergyRaw(Short_t energyRaw)
{
   fEnergyRaw = energyRaw;
}
void HTSimpleDetector::SetTimeRaw(Double_t timeRaw)
{
   fTimeRaw = timeRaw;
}

void HTSimpleDetector::Clear()
{
   fEnergyRaw = -999;
   fTimeRaw = -9999;
   fEnergy = -9999;
   fTime = -9999;
}

void HTSimpleDetector::Calibrate(const json &calibration)
{
   // For this detectir calibration should have the form
   //  {fEnergy:{ calibrationMethod },
   //   fTime: {calibrationMethod }}
   //  If one of the two is now found, just copy the raw data over.
   //  Calibration method can be found in

   // Calibrate energy
   if (calibration.contains("fEnergy"))
      fEnergy = HTCalibrator::Instance()->Calibrate(fEnergyRaw, calibration["fEnergy"]);
   else
      fEnergy = fEnergyRaw;

   // Calibrate time
   if (calibration.contains("fTime"))
      fTime = HTCalibrator::Instance()->Calibrate(fTimeRaw, calibration["fTime"]);
   else
      fTime = fTimeRaw;
}

ClassImp(HTSimpleDetector);
