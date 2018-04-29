#include <HTDetectorMap.h>

//________________________________________________
HTDetectorMap::HTDetectorMap(const char * name) :
fName(name),
fModuleAssignmentOrder(0)
{
  fModuleAssignmentOrder = new std::map<std::string, int>;
}

//________________________________________________
HTDetectorMap::~HTDetectorMap()
{
  if(fModuleAssignmentOrder) {
    delete fModuleAssignmentOrder;
  }
}

//________________________________________________
int HTDetectorMap::LoadMapping(const char * file_name)
{
  std::ifstream FileIn(file_name);

  if(!FileIn.is_open()) {
    return -1;
  }

  int NChannelsMapped=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("assign ")!=std::string::npos) {
      if(LineReadCommentLess.find(fName)!=std::string::npos) {
        ParseAssignLine(LineReadCommentLess.c_str());
      }
    }
    if(LineReadCommentLess.find("map ")!=std::string::npos) {
      if(LineReadCommentLess.find(fName)!=std::string::npos) {
        NChannelsMapped+=ParseMapLine(LineReadCommentLess.c_str());
      }
    }
  }
  FileIn.close();

  return NChannelsMapped;
}

//________________________________________________
int HTDetectorMap::ParseAssignLine(const char * line_to_parse)
{
  int NModulesAdded=fModuleAssignmentOrder->size();

  std::string LineReadCommentLess(line_to_parse);
  if(LineReadCommentLess.find("module ")!=std::string::npos) {
    LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("module ")+7));
    std::istringstream LineStream(LineReadCommentLess);
    std::string DetectorName;
    LineStream>>DetectorName;
    std::string ModuleName;
    if(DetectorName.compare(fName)!=0) return 0;
    while(LineStream>>ModuleName) {
      (*fModuleAssignmentOrder)[ModuleName]=NModulesAdded;
      NModulesAdded++;
    }
  }

  return NModulesAdded;
}

//________________________________________________
int HTDetectorMap::ParseMapLine(const char * line_to_parse)
{
  return 0;
}

//________________________________________________
void HTDetectorMap::Clear()
{
  fModuleAssignmentOrder->clear();
}
