#include <HTVetoWallMap.h>

//________________________________________________
HTVetoWallMap::HTVetoWallMap(const char * name, int num_bars) : HTDetectorMap(name),
fNumBars(num_bars),
fBottomModule(0),
fBottomChannel(0),
fTopModule(0),
fTopChannel(0),
fBottomTimeModule(0),
fBottomTimeChannel(0),
fTopTimeModule(0),
fTopTimeChannel(0)
{
  fBottomModule= new int[fNumBars];
  fBottomChannel= new int[fNumBars];
  fTopModule= new int[fNumBars];
  fTopChannel= new int[fNumBars];
  fBottomTimeModule= new int[fNumBars];
  fBottomTimeChannel= new int[fNumBars];
  fTopTimeModule= new int[fNumBars];
  fTopTimeChannel= new int[fNumBars];

  Clear();
}

//________________________________________________
HTVetoWallMap::~HTVetoWallMap()
{
  if(fBottomModule) delete [] fBottomModule;
  if(fBottomChannel) delete [] fBottomChannel;
  if(fTopModule) delete [] fTopModule;
  if(fTopChannel) delete [] fTopChannel;
  if(fBottomTimeModule) delete [] fBottomTimeModule;
  if(fBottomTimeChannel) delete [] fBottomTimeChannel;
  if(fTopTimeModule) delete [] fTopTimeModule;
  if(fTopTimeChannel) delete [] fTopTimeChannel;
}

//________________________________________________
void HTVetoWallMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumBars; i++) {
    fBottomModule[i]=-1;
    fBottomChannel[i]=-1;
    fTopModule[i]=-1;
    fTopChannel[i]=-1;
    fBottomTimeModule[i]=-1;
    fBottomTimeChannel[i]=-1;
    fTopTimeModule[i]=-1;
    fTopTimeChannel[i]=-1;
  }
}

//________________________________________________
int HTVetoWallMap::ParseMapLine(const char * line_to_parse)
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

  if(ChName.compare("BOTTOM")==0) {
    fBottomModule[DetectorNumber]=ModuleNumber;
    fBottomChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("BOTTOMTIME")==0) {
    fBottomTimeModule[DetectorNumber]=ModuleNumber;
    fBottomTimeChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("TOP")==0) {
    fTopModule[DetectorNumber]=ModuleNumber;
    fTopChannel[DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("TOPTIME")==0) {
    fTopTimeModule[DetectorNumber]=ModuleNumber;
    fTopTimeChannel[DetectorNumber]=ModuleChannel;
  }

  return 1;
}
