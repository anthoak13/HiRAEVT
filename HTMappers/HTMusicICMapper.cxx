#include "HTMusicICMapper.h"

#include "TString.h"

#include "HTMapper.h"
#include "HTMusicIC.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"

#include <string>

HTMusicICMapper::HTMusicICMapper(const json &config) : HTDetectorMapper(config)
{
   fDetector = new HTMusicIC(fConfiguration["detectorName"].get<std::string>());
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
   det->SetEnergyDSLeftRaw(
      mapper->GetAdcEnergy(fConfiguration["fEnergyDSRight"]["moduleName"], fConfiguration["fEnergyDSRight"]["ch"]));
   // Map the triangle pad times
   det->SetTimeUSLeftRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeUSLeft"]["moduleName"], fConfiguration["fTimeUSLeft"]["ch"]));
   det->SetTimeUSRightRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeUSRight"]["moduleName"], fConfiguration["fTimeUSRight"]["ch"]));
   det->SetTimeDSLeftRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeDSLeft"]["moduleName"], fConfiguration["fTimeDSLeft"]["ch"]));
   det->SetTimeDSLeftRaw(
      mapper->GetTimeSingleHit(fConfiguration["fTimeDSRight"]["moduleName"], fConfiguration["fTimeDSRight"]["ch"]));

   det->Calibrate(fCalibration);
}
