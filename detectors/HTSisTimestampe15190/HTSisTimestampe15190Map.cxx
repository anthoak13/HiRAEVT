#include <HTSisTimestampe15190Map.h>

//________________________________________________
HTSisTimestampe15190Map::HTSisTimestampe15190Map(const std::string& name) :
  HTDetectorMap(name),
  fTimestampModule(-1),
  fTimestampKoreansModule(-1)
{}

//________________________________________________
HTSisTimestampe15190Map::~HTSisTimestampe15190Map()
{}

//________________________________________________
int HTSisTimestampe15190Map::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string ModuleName;
  LineStream>>DetectorName>>ChName>>ModuleName;
  if(DetectorName.compare(fName)!=0) return 0;

  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];

  if(ChName.compare("TIMESTAMP")) {
    fTimestampModule=ModuleNumber;
  } else if (ChName.compare("TIMESTAMPKOREANS")) {
    fTimestampKoreansModule=ModuleNumber;
  }

  return 1;
}

//________________________________________________
int HTSisTimestampe15190Map::GetTimestampModule() const
{
  return fTimestampModule;
}

//________________________________________________
int HTSisTimestampe15190Map::GetTimestampKoreansModule() const
{
  return fTimestampKoreansModule;
}
