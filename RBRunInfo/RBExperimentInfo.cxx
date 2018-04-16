#include <RBExperimentInfo.h>

//________________________________________________
RBExperimentInfo::RBExperimentInfo() :
fFirstRun(0),
fLastRun(0)
{}

//________________________________________________
RBExperimentInfo::~RBExperimentInfo()
{}

//________________________________________________
void RBExperimentInfo::Clear()
{
  fDAQConfigurationFileName.clear();
  fPedestalFileName.clear();
  fMappingFileName.clear();
}

//________________________________________________
int RBExperimentInfo::InitClass(const char *file_name)
{
  Clear();
  
  return LoadConfiguration(file_name);
}

//________________________________________________
int RBExperimentInfo::LoadConfiguration(const char *file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  
  int NRead=0;
  
  while (!FileIn.eof()) 
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));
    
    if(LineReadCommentLess.empty()) continue;
    
    std::istringstream LineStream(LineReadCommentLess);
    
    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      
    }
    
    if(LineReadCommentLess.find("FIRST_RUN")!=std::string::npos) {
      fFirstRun=atoi(LineReadCommentLess.substr(LineReadCommentLess.find("=")+1).c_str());
    }
    if(LineReadCommentLess.find("LAST_RUN")!=std::string::npos) {
      fLastRun=atoi(LineReadCommentLess.substr(LineReadCommentLess.find("=")+1).c_str());
    }
    
    NRead++;
  }
  
  return NRead;
}

//________________________________________________
RBRunInfo * RBExperimentInfo::GetRunInfo(int run_num)
{
  RBRunInfo * newRunInfo = new RBRunInfo(run_num);
  
  if(!newRunInfo->LoadDAQSettings(fDAQConfigurationFileName[run_num-fFirstRun])) {
    delete newRunInfo;
    return 0;
  }
  if(!newRunInfo->LoadPedestals(fPedestalFileName[run_num-fFirstRun])) {
    delete newRunInfo;
    return 0;
  }
  if(!newRunInfo->LoadMapping(fMappingFileName[run_num-fFirstRun])) {
    delete newRunInfo;
    return 0;
  }
  
  return newRunInfo;
}

