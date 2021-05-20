#include "HTTimestampMapper.h"
#include "HTTimestamp.h"
#include "HTRootSisTimestamp.h"
#include "HTMapper.h"

#include <string>

HTTimestampMapper::HTTimestampMapper(const json &config) : HTDetectorMapper(config)
{

   TString detName = fConfiguration["detectorName"].get<std::string>();
   fDetector = new HTTimestamp(detName);
   
}

HTTimestampMapper::~HTTimestampMapper() {}

void HTTimestampMapper::MapAndCalibrate()
{

   auto det = dynamic_cast<HTTimestamp *>(fDetector);
   auto moduleMap = HTMapper::Instance()->GetRootModules();

   std::string moduleName = fConfiguration["fTimestamp"]["moduleName"];
   auto module = dynamic_cast<HTRootSisTimestamp *>(moduleMap->at(moduleName));
   int ch = fConfiguration["fTimestamp"]["ch"];

   if(module == nullptr)
      throw std::invalid_argument(std::string("Could not map fTimestamp using module name ")
				  .append(moduleName)
				  .append(" either it does not exist or is the wrong type."));

   det->SetTimestamp(module->GetData(ch));
   
}
