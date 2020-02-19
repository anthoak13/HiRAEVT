/* Implementation for Singeleton factory for detector creation
 *
 * Adam Anthony 7/25/2019
 * 
 */
#include "HTDetectorFactory.h"

HTDetectorFactory* HTDetectorFactory::_instance = nullptr;

HTDetectorFactory::HTDetectorFactory()
{}

HTDetectorFactory::~HTDetectorFactory()
{}

HTDetectorFactory* HTDetectorFactory::Instance()
{
  if (_instance == nullptr)
  {
    _instance = new HTDetectorFactory();
  }

  return _instance;
}

HTDetector* HTDetectorFactory::CreateDetector(const std::string& detType,
					      const std::string& detName,
					      const int numDets)
{
  HTDetector *newDet = nullptr;
  
  if(detType.compare("TDCSpare")==0)
    newDet = new HTTDCSpare(detName.c_str());

  if(detType.compare("HiRA")==0)
    newDet = new HTHiRA(detName.c_str(), numDets);
  
  if(detType.compare("NuetronWall")==0)
    newDet = new HTNeutronWall(detName.c_str(), numDets);

  if(detType.compare("VetoWall")==0)
    newDet = new HTVetoWall(detName.c_str(), numDets);

  if(detType.compare("ForwardArray")==0)
    newDet = new HTForwardArray(detName.c_str(), numDets);

  if(detType.compare("Microball")==0)
    newDet = new HTMicroball(detName.c_str());

  if(detType.compare("SisTimestamp")==0)
    newDet = new HTSisTimestamp(detName.c_str(), numDets);

  if(detType.compare("IonChamber")==0)
    newDet = new HTIonChamber(detName.c_str(), numDets);

  if(detType.compare("MCP")==0)
    newDet = new HTMCP(detName.c_str(), numDets);
  
  
  if (newDet == nullptr)
    std::cerr << "The detector type " << detType << " was not recognized." << std::endl;
  else
    newDet->InitMapping();

  return newDet;
}

