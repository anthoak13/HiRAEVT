#include <HTNeutronWallMap.h>

//________________________________________________
HTNeutronWallMap::HTNeutronWallMap(const char * name) : HTDetectorMap(name),
fLeftModule(-1),
fLeftChannel(-1),
fLeftFastModule(-1),
fLeftFastChannel(-1),
fRightModule(-1),
fRightChannel(-1),
fRightFastModule(-1),
fRightFastChannel(-1),
fLeftTimeModule(-1),
fLeftTimeChannel(-1),
fRightTimeModule(-1),
fRightTimeChannel(-1)
{}

//________________________________________________
HTNeutronWallMap::~HTNeutronWallMap()
{}

//________________________________________________
int HTNeutronWallMap::ParseMapLine(const char * line_to_parse)
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

  if(ChName.compare("LEFT")) {
    fLeftModule=ModuleNumber;
    fLeftChannel=ModuleChannel;
  } else if (ChName.compare("LEFTFAST")) {
    fLeftFastModule=ModuleNumber;
    fLeftFastChannel=ModuleChannel;
  } else if (ChName.compare("LEFTTIME")) {
    fLeftTimeModule=ModuleNumber;
    fRightTimeChannel=ModuleChannel;
  } else if (ChName.compare("RIGHT")) {
    fRightModule=ModuleNumber;
    fRightChannel=ModuleChannel;
  } else if (ChName.compare("RIGHTFAST")) {
    fRightFastModule=ModuleNumber;
    fRightFastChannel=ModuleChannel;
  } else if (ChName.compare("RIGHTTIME")) {
    fRightTimeModule=ModuleNumber;
    fRightTimeChannel=ModuleChannel;
  }

  return 1;
}
