#include "HTSimpleDetectorMapper.h"

#include "HTMapper.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"
#include "HTSimpleDetector.h"

#include <string>

#include "nlohmann/json.hpp"

HTSimpleDetectorMapper::HTSimpleDetectorMapper(const json &config) : fConfig(config)
{
   TString detName = fConfig["detectorName"].get<std::string>();

   // Create the detector we will be filling
   fDetector = new HTSimpleDetector(detName);
}
HTSimpleDetectorMapper::~HTSimpleDetectorMapper() {}

void HTSimpleDetectorMapper::Map()
{

   // Turn the detector into the right pointer
   auto det = dynamic_cast<HTSimpleDetector *>(fDetector);
   auto moduleMap = HTMapper::Instance()->GetRootModules();

   // Get energy module and set the data
   auto enModule = dynamic_cast<HTRootAdc *>(moduleMap->at(fConfig["fEnergy"]["moduleName"]));
   if (enModule == nullptr) {
      std::cout << det->GetType() << " does not support module type "
                << "HTRootAdc"
                << " for parameter fEnergy." << std::endl;
      throw std::invalid_argument("Could not map fEnergy");
   }
   det->SetEnergyRaw(enModule->GetData(fConfig["fEnergy"]["ch"]));

   // Get the time module and channel
   auto timeModule = moduleMap->at(fConfig["fTime"]["moduleName"]);
   int timeCh = fConfig["fTime"]["ch"];

   // Check to see if this is single or multi-hit data. Only take first hit in tdc
   if (timeModule->GetType().EqualTo("HTRootCAEN1x90"))
      det->SetTimeRaw(dynamic_cast<HTRootCAEN1x90 *>(timeModule)->GetData(timeCh, 0));
   else if (timeModule->GetType().EqualTo("HTRootCAEN1x90SingleHit"))
      det->SetTimeRaw(dynamic_cast<HTRootCAEN1x90SingleHit *>(timeModule)->GetData(timeCh));
   else {
      std::cout << det->GetType() << " does not support module type " << timeModule->GetType()
                << " for parameter fTime." << std::endl;
      throw std::invalid_argument("Could not map fTime");
   }
}
