#include "HTMusicIC.h"

#include "HTCalibrator.h"

HTMusicIC::HTMusicIC(const TString detectorName)
   : HTDetector(detectorName), fDriftVelocity(1), fTimeOffset(0), fOffsetZ(0), fReferenceTime(0)
{

   fType = "HTMusicIC";
   Clear();
}

HTMusicIC::~HTMusicIC() {}

// Returns the position of the beam at US trianle pads in mm
ROOT::Math::XYZVector HTMusicIC::GetPositionUS()
{
   Double_t posX = (fEnergyUSRight - fEnergyUSLeft) / (fEnergyUSRight + fEnergyUSLeft);
   posX *= 41.; // width of triangle pad in mm.

   Double_t timeY = fTime[0] - fReferenceTime;
   Double_t posY = (timeY + fTimeOffset) * fDriftVelocity;

   Double_t posZ = -124;

   return ROOT::Math::XYZVector(posX, posY, posZ);
}

// Returns the position of the beam at DS trianle pads in mm
ROOT::Math::XYZVector HTMusicIC::GetPositionDS()
{
   Double_t posX = (fEnergyDSRight - fEnergyDSLeft) / (fEnergyDSRight + fEnergyDSLeft);
   posX *= 41.; // width of triangle pad in mm.

   Double_t timeY = fTime[8] - fReferenceTime;
   Double_t posY = (timeY + fTimeOffset) * fDriftVelocity;

   Double_t posZ = +124;

   return ROOT::Math::XYZVector(posX, posY, posZ);
}

ROOT::Math::XYZVector HTMusicIC::GetPosition(Double_t zPosition)
{
   // Get position in center of detector
   auto posCenter = (GetPositionDS() + GetPositionDS()) / 2.0;

   // Get the slope of the beam per mm in z direction
   auto slope = (GetPositionDS() - GetPositionUS());
   slope /= slope.Z();

   // Return the center + mm along z
   return GetPositionUS() + slope * (zPosition + fOffsetZ + 124);
}

void HTMusicIC::Clear()
{
   for (int i = 0; i < 9; ++i) {
      fEnergyRaw[i] = -9999;
      fTimeRaw[i] = -9999;
      fEnergy[i] = -9999;
      fTime[i] = -9999;
   }

   fEnergyDSLeftRaw = -9999;
   fEnergyDSRightRaw = -9999;
   fEnergyUSLeftRaw = -9999;
   fEnergyUSRightRaw = -9999;

   fEnergyDSLeft = -9999;
   fEnergyDSRight = -9999;
   fEnergyUSLeft = -9999;
   fEnergyUSRight = -9999;

   fTimeDSLeftRaw = -9999;
   fTimeDSRightRaw = -9999;
   fTimeUSLeftRaw = -9999;
   fTimeUSRightRaw = -9999;

   fTimeDSLeft = -9999;
   fTimeDSRight = -9999;
   fTimeUSLeft = -9999;
   fTimeUSRight = -9999;
}

void HTMusicIC::Calibrate(const json &calibration)
{
   // Calibrate the energy pads
   if (calibration.contains("fEnergy")) {
      // To pull out the calibration data we need to access each array value
      for (const auto &cal : calibration["fEnergy"].items()) {
         Int_t padToCal = TString(cal.key()).Atoi();
         if (padToCal >= 0 && padToCal < 9)
            fEnergy[padToCal] = HTCalibrator::Calibrate(fEnergyRaw[padToCal], cal.value());
      }
   }
   // Calibrate the time in the energy pads
   if (calibration.contains("fTime"))
      for (const auto &padCal : calibration["fTime"].items()) {
         Int_t padToCal = TString(padCal.key()).Atoi();
         // We have a pad to calibrate. Check if it's a walk offset, if not do normal calibration
         if (padCal.value()["method"] == "walkCorrection")
            fTime[padToCal] = fTimeRaw[padToCal] - HTCalibrator::TimeWalkOffset(fEnergyRaw[padToCal], padCal.value());
         else
            fTime[padToCal] = HTCalibrator::Calibrate(fTimeRaw[padToCal], padCal.value());

      } // End loop over all energy pad time calibrations

   // Calibrate energy in triangle pads
   if (calibration.contains("fEnergyDSRight"))
      fEnergyDSRight = HTCalibrator::Calibrate(fEnergyDSRightRaw, calibration["fEnergyDSRight"]);
   if (calibration.contains("fEnergyDSLeft"))
      fEnergyDSLeft = HTCalibrator::Calibrate(fEnergyDSLeftRaw, calibration["fEnergyDSLeft"]);
   if (calibration.contains("fEnergyUSRight"))
      fEnergyUSRight = HTCalibrator::Calibrate(fEnergyUSRightRaw, calibration["fEnergyUSRight"]);
   if (calibration.contains("fEnergyUSLeft"))
      fEnergyUSLeft = HTCalibrator::Calibrate(fEnergyUSLeftRaw, calibration["fEnergyUSLeft"]);

   // Calibrate time in triangle pads
   if (calibration.contains("fTimeDSRight")) {
      if (calibration["fTimeDSRight"]["method"] == "walkCorrection")
         fTimeDSRight = fTimeDSRightRaw - HTCalibrator::TimeWalkOffset(fEnergyDSRightRaw, calibration["fTimeDSRight"]);
      else
         fTimeDSRight = HTCalibrator::Calibrate(fTimeDSRightRaw, calibration["fTimeDSRight"]);
   }
   if (calibration.contains("fTimeDSLeft")) {
      if (calibration["fTimeDSLeft"]["method"] == "walkCorrection")
         fTimeDSLeft = fTimeDSLeftRaw - HTCalibrator::TimeWalkOffset(fEnergyDSLeftRaw, calibration["fTimeDSLeft"]);
      else
         fTimeDSLeft = HTCalibrator::Calibrate(fTimeDSLeftRaw, calibration["fTimeDSLeft"]);
   }
   if (calibration.contains("fTimeUSRight")) {
      if (calibration["fTimeUSRight"]["method"] == "walkCorrection")
         fTimeUSRight = fTimeUSRightRaw - HTCalibrator::TimeWalkOffset(fEnergyUSRightRaw, calibration["fTimeUSRight"]);
      else
         fTimeUSRight = HTCalibrator::Calibrate(fTimeUSRightRaw, calibration["fTimeUSRight"]);
   }
   if (calibration.contains("fTimeUSLeft")) {
      if (calibration["fTimeUSLeft"]["method"] == "walkCorrection")
         fTimeUSLeft = fTimeUSLeftRaw - HTCalibrator::TimeWalkOffset(fEnergyUSLeftRaw, calibration["fTimeUSLeft"]);
      else
         fTimeUSLeft = HTCalibrator::Calibrate(fTimeUSLeftRaw, calibration["fTimeUSLeft"]);
   }
}

void HTMusicIC::SetEnergyRaw(Int_t ch, Short_t energy)
{
   if (ch < 9 && ch >= 0)
      fEnergyRaw[ch] = energy;
}
void HTMusicIC::SetTimeRaw(Int_t ch, Double_t time)
{
   if (ch < 9 && ch >= 0)
      fTimeRaw[ch] = time;
}

Short_t HTMusicIC::GetEnergyRaw(Int_t ch)
{
   if (ch < 9 && ch >= 0)
      return fEnergyRaw[ch];
   else
      return -9999;
}
Double_t HTMusicIC::GetTimeRaw(Int_t ch)
{
   if (ch < 9 && ch >= 0)
      return fTimeRaw[ch];
   else
      return -9999;
}
Double_t HTMusicIC::GetEnergy(Int_t ch)
{
   if (ch < 9 && ch >= 0)
      return fEnergy[ch];
   else
      return -9999;
}
Double_t HTMusicIC::GetTime(Int_t ch)
{
   if (ch < 9 && ch >= 0)
      return fTime[ch];
   else
      return -9999;
}

ClassImp(HTMusicIC)
