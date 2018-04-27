#include <HTVetoWallMap.h>

//________________________________________________
HTVetoWallMap::HTVetoWallMap(const char * name) : HTDetectorMap(name),
fBottomModule(-1),
fBottomChannel(-1),
fTopModule(-1),
fTopChannel(-1),
fBottomTimeModule(-1),
fBottomTimeChannel(-1),
fTopTimeModule(-1),
fTopTimeChannel(-1)
{}

//________________________________________________
HTVetoWallMap::~HTVetoWallMap()
{}

//________________________________________________
int HTVetoWallMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string ModuleName;
  std::string ModuleChannelString;
  LineStream>>DetectorName>>ChName>>ModuleName>>ModuleChannelString;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorName.assign(DetectorName.substr(DetectorName.find("detector=\"")+10,DetectorName.find_last_of("\"")-(DetectorName.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));

  int DetectorNumber=std::stoi(DetectorName);
  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("BOTTOM")) {
    fBottomModule=ModuleNumber;
    fBottomChannel=ModuleChannel;
  } else if (ChName.compare("BOTTOMTIME")) {
    fBottomTimeModule=ModuleNumber;
    fTopTimeChannel=ModuleChannel;
  } else if (ChName.compare("TOP")) {
    fTopModule=ModuleNumber;
    fTopChannel=ModuleChannel;
  } else if (ChName.compare("TOPTIME")) {
    fTopTimeModule=ModuleNumber;
    fTopTimeChannel=ModuleChannel;
  }

  return 1;
}
