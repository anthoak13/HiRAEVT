#include <HTIonChamberMap.h>

//________________________________________________
HTIonChamberMap::HTIonChamberMap(const std::string& name, int num_detectors) : HTDetectorMap(name),
fNumDetectors(num_detectors)
{
  fEnergyModule=new int[fNumDetectors];
  fEnergyChannel=new int[fNumDetectors];
  fTimeModule=new int[fNumDetectors];
  fTimeChannel=new int[fNumDetectors];

  Clear();
}

//________________________________________________
HTIonChamberMap::~HTIonChamberMap()
{
  if(fEnergyModule) delete [] fEnergyModule;
  if(fEnergyChannel) delete [] fEnergyChannel;
  if(fTimeModule) delete [] fTimeModule;
  if(fTimeChannel) delete [] fTimeChannel;
}

//________________________________________________
void HTIonChamberMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumDetectors; i++) {
    fEnergyModule[i]  = -1;
    fEnergyChannel[i] = -1;
    fTimeModule[i]    = -1;
    fTimeChannel[i]   = -1;
  }
}

//String has the format "map DetectorName ChType DetectorNumber ModuleName ModuleNumber"
int HTIonChamberMap::ParseMapLine(const char * line_to_parse)
{
  //This is a map string so create a stream to read it
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));

  std::string DetectorName, ChType, ModuleName;
  int detNumber, moduleNumber, moduleCh;
  
  //Load in all of the info
  LineStream >> DetectorName >> ChType >> detNumber >> ModuleName >> moduleCh;

  // Make sure this is the right detector
  if(DetectorName.compare(fName)!=0) return 0;

  //Get the module number from the map
  moduleNumber=fModuleAssignmentOrder->at(ModuleName);


  if(ChType.compare("ENERGY") == 0)
  {
    fEnergyModule[detNumber] = moduleNumber;
    fEnergyChannel[detNumber]= moduleCh;
  }
  else if (ChType.compare("TIME") == 0)
  {
    fTimeModule[detNumber]  = moduleNumber;
    fTimeChannel[detNumber] = moduleCh;
  }
  return 1;
}
