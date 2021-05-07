#include "HTSimpleDetectorMapper.h"

#include "HTMapper.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"
#include "HTSimpleDetector.h"

#include <fstream>
#include <string>

#include "nlohmann/json.hpp"

HTSimpleDetectorMapper::HTSimpleDetectorMapper(const json &config) : HTDetectorMapper(config)
{
   TString detName = fConfiguration["detectorName"].get<std::string>();

   // Create the detector we will be filling
   fDetector = new HTSimpleDetector(detName);
}
HTSimpleDetectorMapper::~HTSimpleDetectorMapper() {}

void HTSimpleDetectorMapper::MapAndCalibrate()
{

   // Turn the detector into the right pointer
   auto det = dynamic_cast<HTSimpleDetector *>(fDetector);
   auto moduleMap = HTMapper::Instance()->GetRootModules(); // Get the availible from HTMapper

   // Get energy module and channel to set
   std::string moduleName = fConfiguration["fEnergy"]["moduleName"];
   auto enModule = dynamic_cast<HTRootAdc *>(moduleMap->at(moduleName));
   int enCh = fConfiguration["fEnergy"]["ch"];

   // Check to make sure energy module is valid and set the energy if it is
   if (enModule == nullptr)
      throw std::invalid_argument(std::string("Could not map fEnergy using module name ")
                                     .append(moduleName)
                                     .append(" either it does not exist or is the wrong type."));
   det->SetEnergyRaw(enModule->GetData(enCh));

   // Get the time module and channel
   moduleName = fConfiguration["fTime"]["moduleName"];
   auto timeModule = moduleMap->at(moduleName);
   int timeCh = fConfiguration["fTime"]["ch"];

   // Check to see if this is single or multi-hit data. Only take first hit in tdc
   if (timeModule->GetType().EqualTo("HTRootCAEN1x90"))
      det->SetTimeRaw(dynamic_cast<HTRootCAEN1x90 *>(timeModule)->GetData(timeCh, 0));
   else if (timeModule->GetType().EqualTo("HTRootCAEN1x90SingleHit"))
      det->SetTimeRaw(dynamic_cast<HTRootCAEN1x90SingleHit *>(timeModule)->GetData(timeCh));
   else
      throw std::invalid_argument(std::string("Could not map fTime using module name ")
                                     .append(moduleName)
                                     .append(" either it does not exist or is the wrong type."));
   // Calibrate data
   det->Calibrate(fCalibration);
}
