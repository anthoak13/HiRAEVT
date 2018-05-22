#include <HTTDCSpareMap.h>

//________________________________________________
HTTDCSpareMap::HTTDCSpareMap(const char * name) : HTDetectorMap(name),
fNumChannels(0)
{
  Clear();
}

//________________________________________________
HTTDCSpareMap::~HTTDCSpareMap()
{}

//________________________________________________
void HTTDCSpareMap::Clear()
{
  fNumChannels=0;
  fModule.clear();
  fChannel.clear();
  fModuleAssignmentOrder->clear();
}

//________________________________________________
int HTTDCSpareMap::ParseMapLine(const char * line_to_parse)
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

  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];
  int ModuleChannel=std::stoi(ModuleChannelString);

  fNumChannels++;
  fModule.push_back(ModuleNumber);
  fChannel.push_back(ModuleChannel);
  fChannelName.push_back(DetectorToSet);

  return 1;
}
