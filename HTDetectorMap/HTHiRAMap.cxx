#include <HTHiRAMap.h>

//________________________________________________
HTHiRAMap::HTHiRAMap(const char * name, int num_telescopes) : HTDetectorMap(name),
fNumTelescopes(num_telescopes)
{

  Clear();
}

//________________________________________________
HTHiRAMap::~HTHiRAMap()
{}

//________________________________________________
void HTHiRAMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumTelescopes; i++) {
  }
}

//________________________________________________
int HTHiRAMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string DetectorToSet;
  std::string ModuleName;
  LineStream>>DetectorName>>ChName>>DetectorToSet>>ModuleName;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));

  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];

  if(ChName.compare("EF")==0) {
    int TelNumber=std::stoi(DetectorToSet);
  } else if (ChName.compare("EB")==0) {
    int TelNumber=std::stoi(DetectorToSet);
  } else if (ChName.compare("CSIENE")==0) {
    int TelNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("TEL")+3, DetectorToSet.find("_")-(DetectorToSet.find("TEL")+3)));
    int CsINumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("CsI")+3));
  } else if (ChName.compare("CSITIME")==0) {
    int TelNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("TEL")+3, DetectorToSet.find("_")-(DetectorToSet.find("TEL")+3)));
    int CsINumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("CsI")+3));
  }

  return 1;
}
