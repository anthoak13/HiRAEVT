#include "HTMcp.h"
// Implementation of HTMcp

#include "HTCalibrator.h"

HTMcp::HTMcp(const TString detectorName) : HTDetector(detectorName)
{
   fType = "HTMcp";

   Clear();
}

HTMcp::~HTMcp() {}

void HTMcp::SetEnergyMcpRaw(Short_t energy)
{
   fEnergyMcpRaw = energy;
}
void HTMcp::SetEnergyAnodeRaw(Short_t energy)
{
   fEnergyAnodeRaw = energy;
}
void HTMcp::SetTimeMcpRaw(const vecDouble &time)
{
   fTimeMcpRaw = time;
}
void HTMcp::SetTimeAnodeRaw(const vecDouble &time)
{
   fTimeAnodeRaw = time;
}

void HTMcp::Clear()
{
   fEnergyAnode = -9999;
   fEnergyAnodeRaw = -9999;
   fEnergyMcp = -9999;
   fEnergyMcpRaw = -9999;

   fTimeAnode.clear();
   fTimeAnodeRaw.clear();
   fTimeMcp.clear();
   fTimeMcpRaw.clear();
}

void HTMcp::Calibrate(const json &calibration)
{
   if (calibration.contains("fEnergyMcp"))
      fEnergyMcp = HTCalibrator::Instance()->Calibrate(fEnergyMcpRaw, calibration["fEnergyMcp"]);
   else
      fEnergyMcp = fEnergyMcpRaw;

   if (calibration.contains("fEnergyAnode"))
      fEnergyAnode = HTCalibrator::Instance()->Calibrate(fEnergyAnodeRaw, calibration["fEnergyAnode"]);
   else
      fEnergyAnode = fEnergyAnodeRaw;

   if (calibration.contains("fTimeMcp"))
      for (const auto &time : fTimeMcpRaw)
         fTimeMcp.push_back(HTCalibrator::Instance()->Calibrate(time, calibration["fTimeMcp"]));
   else
      fTimeMcp = fTimeMcpRaw;

   if (calibration.contains("fTimeAnode"))
      for (const auto &time : fTimeAnodeRaw)
         fTimeAnode.push_back(HTCalibrator::Instance()->Calibrate(time, calibration["fTimeAnode"]));
   else
      fTimeAnode = fTimeAnodeRaw;
}

ClassImp(HTMcp)
