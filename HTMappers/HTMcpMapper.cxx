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

   // Set the anode energy
   det->SetEnergyAnodeRaw(HTMapper::Instance()->GetAdcEnergy(fConfiguration["fEnergyAnode"]["moduleName"],
                                                             fConfiguration["fEnergyAnode"]["ch"]));

   // Set the mcp energy
   det->SetEnergyMcpRaw(HTMapper::Instance()->GetAdcEnergy(fConfiguration["fEnergyMcp"]["moduleName"],
                                                           fConfiguration["fEnergyMcp"]["ch"]));

   // Set anode time
   det->SetTimeAnodeRaw(HTMapper::Instance()->GetTimeMultiHit(fConfiguration["fTimeAnode"]["moduleName"],
                                                              fConfiguration["fTimeAnode"]["ch"]));

   // Set MCP time
   det->SetTimeMcpRaw(HTMapper::Instance()->GetTimeMultiHit(fConfiguration["fTimeMcp"]["moduleName"],
                                                            fConfiguration["fTimeMcp"]["ch"]));

   det->Calibrate(fCalibration);
}
