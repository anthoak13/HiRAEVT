#include "HTMusicICMapper.h"

#include "TString.h"

#include "HTMapper.h"
#include "HTMusicIC.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"

#include <fstream>
#include <string>

HTMusicICMapper::HTMusicICMapper(const json &config) : HTDetectorMapper(config)
{
   fDetector = new HTMusicIC(fConfiguration["detectorName"].get<std::string>());

   // Check to see if a gasFile was passed and if so open in
   if (fConfiguration.contains("gasFile")) {
      std::fstream gasFile(fConfiguration["gasFile"]);
      if (!gasFile)
         throw std::invalid_argument("Can not open gas file: " + fConfiguration["gasFile"].get<std::string>());

      json gasInfo;
      gasFile >> gasInfo;

      // Loop through and look for something that matches this tun
      for (const auto &info : gasInfo["gasList"]) {
         bool rightInfo = false;
         auto runNumber = HTMapper::Instance()->GetRunNumber();

         // Check if this is a single run entry and if it is if it matches our run number
         rightInfo |= info.value("run", -1) == runNumber;

         if (info.contains("runRange"))
            rightInfo |= (info["runRange"][0] <= runNumber && info["runRange"][1] >= runNumber);

         // We found the right object
         if (rightInfo) {
            std::cout << "Setting drift velocity: " << info["driftVelocity"] << " mm/ns" << std::endl
                      << "Setting time offset: " << info["timeOffset"] << " ns" << std::endl;
            dynamic_cast<HTMusicIC *>(fDetector)->SetDriftVelocity(info["driftVelocity"]);
            dynamic_cast<HTMusicIC *>(fDetector)->SetTimeOffset(info["timeOffset"]);
         } //if we found right into
      } //Loop over gas info json objects
   } // There was a gasFile to lookup
}

HTMusicICMapper::~HTMusicICMapper() {}

void HTMusicICMapper::MapAndCalibrate()
{
   // Cast the detector into the right type
   auto det = dynamic_cast<HTMusicIC *>(fDetector);
   auto mapper = HTMapper::Instance();

   // Map the rectangle pads
   for (int i = 0; i < 9; ++i) {
      Short_t en = mapper->GetAdcEnergy(fConfiguration["fEnergy"][i]["moduleName"], fConfiguration["fEnergy"][i]["ch"]);
      det->SetEnergyRaw(i, en);

      auto time = mapper->GetTimeSingleHit(fConfiguration["fTime"][i]["moduleName"], fConfiguration["fTime"][i]["ch"]);
      det->SetTimeRaw(i, time);
   }

   // Map the triangle pad energies
   det->SetEnergyUSLeftRaw(
      mapper->GetAdcEnergy(fConfiguration["fEnergyUSLeft"]["moduleName"], fConfiguration["fEnergyUSLeft"]["ch"]));
   det->SetEnergyUSRightRaw(
      mapper->GetAdcEnergy(fConfiguration["fEnergyUSRight"]["moduleName"], fConfiguration["fEnergyUSRight"]["ch"]));
   det->SetEnergyDSLeftRaw(
      mapper->GetAdcEnergy(fConfiguration["fEnergyDSLeft"]["moduleName"], fConfiguration["fEnergyDSLeft"]["ch"]));
   det->SetEnergyDSRightRaw(
      mapper->GetAdcEnergy(fConfiguration["fEnergyDSRight"]["moduleName"], fConfiguration["fEnergyDSRight"]["ch"]));
   // Map the triangle pad times
   det->SetTimeUSLeftRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeUSLeft"]["moduleName"], fConfiguration["fTimeUSLeft"]["ch"]));
   det->SetTimeUSRightRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeUSRight"]["moduleName"], fConfiguration["fTimeUSRight"]["ch"]));
   det->SetTimeDSLeftRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeDSLeft"]["moduleName"], fConfiguration["fTimeDSLeft"]["ch"]));
   det->SetTimeDSRightRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeDSRight"]["moduleName"], fConfiguration["fTimeDSRight"]["ch"]));

   //Map the reference time
   det->SetReferenceTime(
      mapper->GetTimeSingleHit(fConfiguration["fTimeReference"]["moduleName"], fConfiguration["fTimeReference"]["ch"]));
   
   det->Calibrate(fCalibration);
}
