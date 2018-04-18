#include <RBRunInfo.h>

//________________________________________________
RBRunInfo::RBRunInfo(int run_number, const char * run_title) :
fRunNumber(run_number),
fNStacks(0),
fDAQLoaded(false),
fPedestalsLoaded(false),
fMappingLoaded(false)
{
  SetRunTitle(run_title);
}

//________________________________________________
RBRunInfo::~RBRunInfo()
{
  for(int i=0; i< fNStacks; i++) {
    if (fStackInfo[i]) {
      delete fStackInfo[i];
    }
  }
}

//________________________________________________
int RBRunInfo::LoadDAQSettings(const char * file_name)
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

    if(LineReadCommentLess.find("define ")!=std::string::npos) {
      ParseDefineDAQLine(LineReadCommentLess.c_str()); //adding a new stack
    }
    if(LineReadCommentLess.find("add ")!=std::string::npos) {
      ParseAddDAQLine(LineReadCommentLess.c_str()); //adding a new module to an existing stack
    }
    NRead++;
  }

  fDAQLoaded=true;
  return NRead;
}

//________________________________________________
void RBRunInfo::ParseDefineDAQLine(const char * line_to_parse)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("define ")+7)); //remove define command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;

  if(ValueToSet.compare("stack")==0) {
    fNStacks++;
    std::string NewStackName(LineToParse.substr(LineToParse.find("\"")+1,LineToParse.find_last_of("\"")-(LineToParse.find("\"")+1)));
    int stackID=atoi(LineToParse.substr(LineToParse.find_last_of("\"")+1).c_str());

    // found a new stack. RBDAQStackInfo is being added to the fStackInfo vector
    RBDAQStackInfo * newStack = new RBDAQStackInfo(NewStackName.c_str(), stackID);
    fStackInfo.push_back(newStack);
  }

  return;
}

//________________________________________________
void RBRunInfo::ParseAddDAQLine(const char * line_to_parse)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("add ")+4)); //remove add command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;

  if(ValueToSet.compare("module")==0) {
    int StackID;
    LineStream>>StackID;
    std::string ModuleType;
    LineStream>>ModuleType;
    std::string ModuleName;
    LineStream>>ModuleName;
    int VSN;
    LineStream>>VSN;
    ModuleName.assign(ModuleName.substr(ModuleName.find("\"")+1,ModuleName.find_last_of("\"")-(ModuleName.find("\"")+1)));

    //Found a new module. RBModuleInfo is created and added to the corresponding fStackInfo.
    RBModuleInfo * newModuleInfo = new RBModuleInfo();
    newModuleInfo->SetVSN(VSN);
    newModuleInfo->SetModuleType(ModuleType);
    newModuleInfo->SetModuleName(ModuleName);

    if(ModuleType.compare("RBSisTimestampUnpacker")==0) {
      RBSisTimestampUnpacker * newModule = new RBSisTimestampUnpacker(ModuleName.c_str());
      newModuleInfo->SetModule(newModule);
      fStackInfo[StackID]->AddModuleInfo(newModuleInfo);
      return;
    } else if (ModuleType.compare("RBHINPUnpacker")==0) {
      int NumMotherboard;
      std::string usingFADC;
      LineStream >> NumMotherboard >> usingFADC;
      RBHINPUnpacker * newModule = new RBHINPUnpacker(ModuleName.c_str(),NumMotherboard,usingFADC.compare("false") ? false : true);
      newModuleInfo->SetModule(newModule);
      fStackInfo[StackID]->AddModuleInfo(newModuleInfo);
      return;
    } else if (ModuleType.compare("RBCAEN7xxUnpacker")==0) {
      RBCAEN7xxUnpacker * newModule = new RBCAEN7xxUnpacker(ModuleName.c_str());
      newModuleInfo->SetModule(newModule);
      newModuleInfo->SetNumCh(32);
      fStackInfo[StackID]->AddModuleInfo(newModuleInfo);
      return;
    } else if (ModuleType.compare("RBCAEN1x90Unpacker")==0) {
      int depth, refch, Nchannels;
      double ns_per_ch;
      LineStream>>depth>>refch>>Nchannels>>ns_per_ch;
      RBCAEN1x90Unpacker * newModule = new RBCAEN1x90Unpacker(ModuleName.c_str(),depth, refch, Nchannels,ns_per_ch);
      newModuleInfo->SetModule(newModule);
      newModuleInfo->SetNumCh(Nchannels);
      fStackInfo[StackID]->AddModuleInfo(newModuleInfo);
      return;
    }

    //In case none of the previous options was typed just delete the module
    delete newModuleInfo;
  }

  return;
}

//________________________________________________
int RBRunInfo::LoadPedestals(const char * file_name)
{
  if(!fDAQLoaded) return -1;
  fMappingLoaded=true;
  return 0;
}

//________________________________________________
int RBRunInfo::LoadMapping(const char * file_name)
{
  if(!fDAQLoaded) return -1;
  fPedestalsLoaded=true;
  return 0;
}

//________________________________________________
void RBRunInfo::SetRunTitle(const char * run_title)
{
  fRunTitle.assign(run_title);
}

//________________________________________________
void RBRunInfo::SetEvtFilePath(const char * file_name)
{
  fEvtFilePath.assign(file_name);
}

//________________________________________________
const char * RBRunInfo::GetEvtFilePath() const
{
  return fEvtFilePath.c_str();
}

//________________________________________________
const char * RBRunInfo::GetTitle() const
{
  return fRunTitle.c_str();
}

//________________________________________________
int RBRunInfo::GetRunNumber() const
{
  return fRunNumber;
}

//________________________________________________
int RBRunInfo::GetNStacks() const
{
  return fNStacks;
}

//________________________________________________
RBDAQStackInfo * RBRunInfo::GetStackInfo(int num_stack) const
{
  return fStackInfo[num_stack];
}
