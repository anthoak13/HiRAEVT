#include <RBDAQStackInfo.h>

//________________________________________________
RBDAQStackInfo::RBDAQStackInfo(const char * name, int stackID) :
fNModules(0),
fStackName(name),
fStackID(stackID)
{}

//________________________________________________
RBDAQStackInfo::~RBDAQStackInfo()
{
  Clear();
}

//________________________________________________
void RBDAQStackInfo::Clear()
{
  for(int i=0; i<fNModules; i++) {
    delete fModuleInStack[i];
  }
  fModuleInStack.clear();
  fNModules=0;
}

//________________________________________________
int RBDAQStackInfo::GetNModules() const
{
  return fNModules;
}

//________________________________________________
RBElectronics * RBDAQStackInfo::GetModule(int n_module) const
{
  return fModuleInStack[n_module]->GetModule();
}

//________________________________________________
const char * RBDAQStackInfo::GetModuleType(int n_module) const
{
  return fModuleInStack[n_module]->GetModuleType();
}

//________________________________________________
int RBDAQStackInfo::GetModuleVSN(int n_module) const
{
  return fModuleInStack[n_module]->GetVSN();
}

//________________________________________________
int RBDAQStackInfo::GetStackID() const
{
  return fStackID;
}

//________________________________________________
const char * RBDAQStackInfo::GetStackName() const
{
  return fStackName.c_str();
}

//________________________________________________
RBModuleInfo  * RBDAQStackInfo::GetModuleInfo(int n_module) const
{
  return fModuleInStack[n_module];
}

//________________________________________________
void RBDAQStackInfo::AddModuleInfo(RBModuleInfo * new_module_info)
{
  fNModules++;
  fModuleInStack.push_back(new_module_info);
  return;
}
