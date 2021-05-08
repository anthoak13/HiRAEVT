#include "HTMcpMapper.h"

#include "TString.h"

#include "HTMapper.h"
#include "HTMcp.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"

#include <string>

HTMcpMapper::HTMcpMapper(const json &config) : HTDetectorMapper(config)
{
   TString detName = fConfiguration["detectorName"].get<std::string>();

   fDetector = new HTMcp(detName);
}

HTMcpMapper::~HTMcpMapper() {}

void HTMcpMapper::MapAndCalibrate()
{
   // Turn the detector into the right type
   auto det = dynamic_cast<HTMcp *>(fDetector);
   auto moduleMap = HTMapper::Instance()->GetRootModules();

   // Set the anode energy
   det->SetEnergyAnodeRaw(
      GetEnergy(fConfiguration["fEnergyAnode"]["moduleName"], fConfiguration["fEnergyAnode"]["ch"]));

   // Set the mcp energy
   det->SetEnergyMcpRaw(GetEnergy(fConfiguration["fEnergyMcp"]["moduleName"], fConfiguration["fEnergyMcp"]["ch"]));

   // Set anode time
   det->SetTimeAnodeRaw(GetTime(fConfiguration["fTimeAnode"]["moduleName"], fConfiguration["fTimeAnode"]["ch"]));

   // Set MCP time
   det->SetTimeMcpRaw(GetTime(fConfiguration["fTimeMcp"]["moduleName"], fConfiguration["fTimeMcp"]["ch"]));

   det->Calibrate(fCalibration);
}

Short_t HTMcpMapper::GetEnergy(std::string moduleName, int ch)
{
   // Make sure the module exists
   auto moduleMap = HTMapper::Instance()->GetRootModules();
   if (moduleMap->count(moduleName) == 0)
      throw std::invalid_argument(
         std::string("Could not map an energy using module ").append(moduleName).append(" it does not exist."));

   // Get the energy from the module
   auto module = dynamic_cast<HTRootAdc *>(moduleMap->at(moduleName));
   if (module == nullptr)
      throw std::invalid_argument(std::string("Could not map an energy using module name ")
                                     .append(moduleName)
                                     .append(" it is not of type HTRootAdc."));
   return module->GetData(ch);
}

std::vector<Double_t> HTMcpMapper::GetTime(std::string moduleName, int ch)
{

   // Make sure the module exists
   auto moduleMap = HTMapper::Instance()->GetRootModules();
   if (moduleMap->count(moduleName) == 0)
      throw std::invalid_argument(
         std::string("Could not map an energy using module ").append(moduleName).append(" it does not exist."));

   // Figure out if we are single or multi hit MCP data
   auto timeModule = moduleMap->at(moduleName);

   // If this is a multi-hit tdc
   if (timeModule->GetType().EqualTo("HTRootCAEN1x90")) {
      auto multiHit = dynamic_cast<HTRootCAEN1x90 *>(timeModule);
      return *(multiHit->GetData(ch));
   } else if (timeModule->GetType().EqualTo("HTRootCAEN1x90SingleHit")) {
      auto singleHit = dynamic_cast<HTRootCAEN1x90SingleHit *>(timeModule);
      return std::vector<Double_t>{singleHit->GetData(ch)};
   } else
      throw std::invalid_argument(
         std::string("Could not map time using module ").append(moduleName).append(" it is the wrong type."));
}
