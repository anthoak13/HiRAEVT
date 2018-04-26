#include <HTExperimentalSetup.h>

//________________________________________________
HTExperimentalSetup::HTExperimentalSetup() :
fModules(0)
{
  fModules = new std::map<int, HTRootElectronics*>;
  fModulesNamesMapped = new std::map<std::string, HTRootElectronics*>;
}

//________________________________________________
HTExperimentalSetup::~HTExperimentalSetup()
{
  if(fModules) {
    for(int NumStack=0; NumStack<gRun->GetNStacks(); NumStack++)
    {
      HTDAQStackInfo * newStackInfo = gRun->GetStackInfo(NumStack);
      for(int NumModule=0; NumModule<newStackInfo->GetNModules(); NumModule++)
      {
        HTModuleInfo * newModuleInfo = newStackInfo->GetModuleInfo(NumModule);
        int StacktoDelete=NumStack;
        int VSNtoDelete=newModuleInfo->GetVSN();
        delete (*fModules)[StacktoDelete*100+VSNtoDelete];
      }
    }
    delete fModules;
  }
}

//________________________________________________
int HTExperimentalSetup::BuildElectronicModules()
{
  // Definition of electronic modules to retrieve data from the ROOT Unpacked TTree
  for(int NumStack=0; NumStack<gRun->GetNStacks(); NumStack++)
  {
    //Loop over all the defined stacks to retrieve individual module information
    HTDAQStackInfo * newStackInfo = gRun->GetStackInfo(NumStack);
    for(int NumModule=0; NumModule<newStackInfo->GetNModules(); NumModule++)
    {
      //Loop over all the modules of a stack
      HTModuleInfo * newModuleInfo = newStackInfo->GetModuleInfo(NumModule);
      std::string newModuleType(newModuleInfo->GetModuleType());
      std::string newModuleName(newModuleInfo->GetModuleName());
      int newModuleVSN=abs(newModuleInfo->GetVSN());
      int newModuleStack=NumStack;

      if(newModuleType.compare("RBSisTimestampUnpacker")==0) {
        HTRootSisTimestamp * newModule = new HTRootSisTimestamp(newModuleName.c_str());
        (*fModules)[newModuleStack*100+newModuleVSN]=newModule;
        (*fModulesNamesMapped)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBTimestamp")==0) {
        HTRootTimestamp * newModule = new HTRootTimestamp(newModuleName.c_str());
        (*fModules)[newModuleStack*100+newModuleVSN]=newModule;
        (*fModulesNamesMapped)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBHINPUnpacker")==0) {
        HTRootHINP * newModule = new HTRootHINP(newModuleName.c_str());
        (*fModules)[newModuleStack*100+newModuleVSN]=newModule;
        (*fModulesNamesMapped)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBCAEN7xxUnpacker")==0) {
        HTRootCAEN7xx * newModule = new HTRootCAEN7xx(newModuleName.c_str());
        (*fModules)[newModuleStack*100+newModuleVSN]=newModule;
        (*fModulesNamesMapped)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBCAEN1x90Unpacker")==0) {
        HTRootCAEN1x90 * newModule = new HTRootCAEN1x90(newModuleName.c_str(), newModuleInfo->GetNumCh());
        (*fModules)[newModuleStack*100+newModuleVSN]=newModule;
        (*fModulesNamesMapped)[newModuleName]=newModule;
      }
    }
  }
  return (*fModules).size();
}

//________________________________________________
int HTExperimentalSetup::BuildDetectors()
{
  return fDetectors.size();
}

//________________________________________________
int HTExperimentalSetup::BuildDetectorMaps()
{
  return fDetectorMaps.size();
}

//________________________________________________
std::map<int, HTRootElectronics *> * HTExperimentalSetup::GetModules() const
{
  return fModules;
}

//________________________________________________
HTRootElectronics * HTExperimentalSetup::GetModule(int modid) const
{
  return (*fModules)[modid];
}

//________________________________________________
HTRootElectronics * HTExperimentalSetup::GetModule(const char * name) const
{
  std::string StringName(name);
  return (*fModulesNamesMapped)[StringName];
}

//________________________________________________
HTDetector * HTExperimentalSetup::GetDetector(int detnumer) const
{
  return fDetectors[detnumer];
}

//________________________________________________
int HTExperimentalSetup::GetNDetectors() const
{
  return fDetectors.size();
}
