#include <HTNeutronWallMap.h>

//________________________________________________
HTNeutronWallMap::HTNeutronWallMap(const char * name, int num_bars) : HTDetectorMap(name),
fNumBars(num_bars),
fLeftModule(0),
fLeftChannel(0),
fLeftFastModule(0),
fLeftFastChannel(0),
fRightModule(0),
fRightChannel(0),
fRightFastModule(0),
fRightFastChannel(0),
fLeftTimeModule(0),
fLeftTimeChannel(0),
fRightTimeModule(0),
fRightTimeChannel(0)
{
  fLeftModule=new int[fNumBars];
  fLeftChannel=new int[fNumBars];
  fLeftFastModule=new int[fNumBars];
  fLeftFastChannel=new int[fNumBars];
  fRightModule=new int[fNumBars];
  fRightChannel=new int[fNumBars];
  fRightFastModule=new int[fNumBars];
  fRightFastChannel=new int[fNumBars];
  fLeftTimeModule=new int[fNumBars];
  fLeftTimeChannel=new int[fNumBars];
  fRightTimeModule=new int[fNumBars];
  fRightTimeChannel=new int[fNumBars];

  Clear();
}

//________________________________________________
HTNeutronWallMap::~HTNeutronWallMap()
{
  if(fLeftModule) delete [] fLeftModule;
  if(fLeftChannel) delete [] fLeftChannel;
  if(fLeftFastModule) delete [] fLeftFastModule;
  if(fLeftFastChannel) delete [] fLeftFastChannel;
  if(fRightModule) delete [] fRightModule;
  if(fRightChannel) delete [] fRightChannel;
  if(fRightFastModule) delete [] fRightFastModule;
  if(fRightFastChannel) delete [] fRightFastChannel;
  if(fLeftTimeModule) delete [] fLeftTimeModule;
  if(fLeftTimeChannel) delete [] fLeftTimeChannel;
  if(fRightTimeModule) delete [] fRightTimeModule;
  if(fRightTimeChannel) delete [] fRightTimeChannel;
}

//________________________________________________
void HTNeutronWallMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumBars; i++) {
    fLeftModule[i]=-1;
    fLeftChannel[i]=-1;
    fLeftFastModule[i]=-1;
    fLeftFastChannel[i]=-1;
    fRightModule[i]=-1;
    fRightChannel[i]=-1;
    fRightFastModule[i]=-1;
    fRightFastChannel[i]=-1;
    fLeftTimeModule[i]=-1;
    fLeftTimeChannel[i]=-1;
    fRightTimeModule[i]=-1;
    fRightTimeChannel[i]=-1;
  }
}

//________________________________________________
int HTNeutronWallMap::ParseMapLine(const char * line_to_parse)
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

  int DetectorNumber=std::stoi(DetectorToSet);
  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("LEFT")==0) {
    fLeftModule[DetectorNumber]=ModuleNumber;
    fLeftChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("LEFTFAST")==0) {
    fLeftFastModule[DetectorNumber]=ModuleNumber;
    fLeftFastChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("LEFTTIME")==0) {
    fLeftTimeModule[DetectorNumber]=ModuleNumber;
    fRightTimeChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("RIGHT")==0) {
    fRightModule[DetectorNumber]=ModuleNumber;
    fRightChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("RIGHTFAST")==0) {
    fRightFastModule[DetectorNumber]=ModuleNumber;
    fRightFastChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("RIGHTTIME")==0) {
    fRightTimeModule[DetectorNumber]=ModuleNumber;
    fRightTimeChannel[DetectorNumber]=ModuleChannel;
  }

  return 1;
}
