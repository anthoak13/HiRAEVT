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

void HTSimpleDetector::Calibrate(const json &fCalibration)
{
   // For this detectir calibration should have the form
   //  {fEnergy:{ calibrationMethod },
   //   fTime: {calibrationMethod }}
   //  If one of the two is now found, just copy the raw data over.
   //  Calibration method can be found in

   // Calibrate energy
   if (fCalibration.contains("fEnergy"))
      fEnergy = HTCalibrator::Instance()->Calibrate(fEnergyRaw, fCalibration["fEnergy"]);

   // Calibrate time
   if (fCalibration.contains("fTime"))
      fTime = HTCalibrator::Instance()->Calibrate(fTimeRaw, fCalibration["fTime"]);
}

ClassImp(HTSimpleDetector);
