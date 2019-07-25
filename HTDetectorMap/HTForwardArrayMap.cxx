#include <HTForwardArrayMap.h>

//________________________________________________
HTForwardArrayMap::HTForwardArrayMap(const std::string& name, int num_detectors) :
  HTDetectorMap(name),
  fNumDetectors(num_detectors),
  fEnergyModule(0),
  fEnergyChannel(0),
  fTimeModule(0),
  fTimeChannel(0)
{
  fEnergyModule=new int[fNumDetectors];
  fEnergyChannel=new int[fNumDetectors];
  fTimeModule=new int[fNumDetectors];
  fTimeChannel=new int[fNumDetectors];

  Clear();
}

//________________________________________________
HTForwardArrayMap::~HTForwardArrayMap()
{
  if(fEnergyModule) delete [] fEnergyModule;
  if(fEnergyChannel) delete [] fEnergyChannel;
  if(fTimeModule) delete [] fTimeModule;
  if(fTimeChannel) delete [] fTimeChannel;
}

//________________________________________________
void HTForwardArrayMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumDetectors; i++) {
    fEnergyModule[i]=-1;
    fEnergyChannel[i]=-1;
    fTimeModule[i]=-1;
    fTimeChannel[i]=-1;
  }
}

//________________________________________________
int HTForwardArrayMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string DetectorToSet;
  std::string ModuleName;
  std::string ModuleChannelString;
  LineStream>>DetectorName>>ChName>>DetectorToSet>>ModuleName>>ModuleChannelString;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));

  int DetectorNumber=std::stoi(DetectorToSet)-1; //WARNING: FA detectors start from 1 but the array starts from 0.
  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("ENERGY")==0) {
    fEnergyModule[DetectorNumber]=ModuleNumber;
    fEnergyChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("TIME")==0) {
    fTimeModule[DetectorNumber]=ModuleNumber;
    fTimeChannel[DetectorNumber]=ModuleChannel;
  }

  return 1;
}
