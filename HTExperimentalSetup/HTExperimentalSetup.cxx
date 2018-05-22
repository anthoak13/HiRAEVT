#include <HTExperimentalSetup.h>

//________________________________________________
HTExperimentalSetup::HTExperimentalSetup() :
fModules(0),
fDetectors(0),
fDetectorMaps(0)
{
  fModules = new std::map<std::string, HTRootElectronics*>;
  fDetectors = new std::map<std::string, HTDetector *>;
  fDetectorMaps = new std::map<std::string, HTDetectorMap *>;
}

//________________________________________________
HTExperimentalSetup::~HTExperimentalSetup()
{
  if(fModules) {
    for(std::map<std::string, HTRootElectronics *>::iterator TheModule=fModules->begin(); TheModule!=fModules->end(); TheModule++) {
      delete (*TheModule).second;
    }
    delete fModules;
  }
  if(fDetectors) {
    for(std::map<std::string, HTDetector *>::iterator TheModule=fDetectors->begin(); TheModule!=fDetectors->end(); TheModule++) {
      delete (*TheModule).second;
    }
    delete fDetectors;
  }
  if(fDetectorMaps) {
    for(std::map<std::string, HTDetectorMap *>::iterator TheModule=fDetectorMaps->begin(); TheModule!=fDetectorMaps->end(); TheModule++) {
      delete (*TheModule).second;
    }
    delete fDetectorMaps;
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

      if(newModuleType.compare("RBSisTimestampUnpacker")==0) {
        HTRootSisTimestamp * newModule = new HTRootSisTimestamp(newModuleName.c_str());
        (*fModules)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBTimestamp")==0) {
        HTRootTimestamp * newModule = new HTRootTimestamp(newModuleName.c_str());
        (*fModules)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBHINPUnpacker")==0) {
        HTRootHINP * newModule = new HTRootHINP(newModuleName.c_str());
        (*fModules)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBCAEN7xxUnpacker")==0) {
        HTRootCAEN7xx * newModule = new HTRootCAEN7xx(newModuleName.c_str());
        int LineLoaded=newModule->LoadPedestals(gRun->GetPedestalFile());
        if(LineLoaded<0) {
          printf("HTRootCAEN7xx: Error while loading pedestal file %s\n", gRun->GetPedestalFile());
        } else {
          printf("HTRootCAEN7xx: Module %s has loaded %d lines from pedestal file %s\n", newModuleName.c_str(), LineLoaded, gRun->GetPedestalFile());
        }
        (*fModules)[newModuleName]=newModule;
      } else if (newModuleType.compare("RBCAEN1x90Unpacker")==0) {
        HTRootCAEN1x90 * newModule = new HTRootCAEN1x90(newModuleName.c_str(), newModuleInfo->GetNumCh());
        (*fModules)[newModuleName]=newModule;
      }
    }
  }
  return fModules->size();
}

//________________________________________________
int HTExperimentalSetup::BuildDetectors()
{
  std::ifstream FileIn(gRun->GetMappingFile());
  if(!FileIn.is_open()) {
    printf("HTExperimentalSetup: Failed to build detectors, error while opening %s file\n", gRun->GetMappingFile());
    return -1;
  }

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("define ")!=std::string::npos) {
      ParseDefineMappingLine(LineReadCommentLess.c_str());
    }
    if(LineReadCommentLess.find("assign ")!=std::string::npos) {
      ParseAssignMappingLine(LineReadCommentLess.c_str());
    }
  }
  FileIn.close();

  printf("HTExperimentalSetup: Built %lu detectors from file %s\n", fDetectors->size(), gRun->GetMappingFile());
  return fDetectors->size();
}

//________________________________________________
int HTExperimentalSetup::ParseDefineMappingLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);

  int NDets=fDetectors->size();

  if(LineReadCommentLess.find("detector ")!=std::string::npos) {
    LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("detector ")+9));
    std::istringstream LineStream(LineReadCommentLess);
    std::string DetectorType;
    std::string DetectorName;
    LineStream>>DetectorType>>DetectorName;

    DetectorName.assign(DetectorName.substr(DetectorName.find("\"")+1,DetectorName.find_last_of("\"")-(DetectorName.find("\"")+1)));

    if(DetectorType.compare("TDCSpare")==0) {
      HTTDCSpare * newDetector = new HTTDCSpare(DetectorName.c_str());
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("HiRA")==0) {
      int NumTelescopes;
      LineStream>>NumTelescopes;
      HTHiRA * newDetector = new HTHiRA(DetectorName.c_str(), NumTelescopes);
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("NeutronWall")==0) {
      int NumBars;
      LineStream>>NumBars;
      HTNeutronWall * newDetector = new HTNeutronWall(DetectorName.c_str(), NumBars);
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("VetoWall")==0) {
      int NumBars;
      LineStream>>NumBars;
      HTVetoWall * newDetector = new HTVetoWall(DetectorName.c_str(), NumBars);
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("ForwardArray")==0) {
      int NumDetectors;
      LineStream>>NumDetectors;
      HTForwardArray * newDetector = new HTForwardArray(DetectorName.c_str(), NumDetectors);
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("Microball")==0) {
      HTMicroball * newDetector = new HTMicroball(DetectorName.c_str());
      (*fDetectors)[DetectorName]=newDetector;
    } else if(DetectorType.compare("SisTimestampe15190")==0) {
      HTSisTimestampe15190 * newDetector = new HTSisTimestampe15190(DetectorName.c_str());
      (*fDetectors)[DetectorName]=newDetector;
    }
  }

  return fDetectors->size()-NDets;
}

//________________________________________________
int HTExperimentalSetup::ParseAssignMappingLine(const char * line_to_parse)
{
  int NModulesAdded=0;

  std::string LineReadCommentLess(line_to_parse);
  if(LineReadCommentLess.find("module ")!=std::string::npos) {
    LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("module ")+7));
    std::istringstream LineStream(LineReadCommentLess);
    std::string DetectorName;
    LineStream>>DetectorName;
    std::string ModuleName;
    while(LineStream>>ModuleName) {
      if(fDetectors->find(DetectorName)!=fDetectors->end()) {
        NModulesAdded++;
        (*fDetectors)[DetectorName]->AssignModule((*fModules)[ModuleName]);
      }
    }
  }

  return NModulesAdded;
}

//________________________________________________
int HTExperimentalSetup::BuildDetectorMaps()
{
  // Loop over the defined detectors to build the corresponding detector mappers
  // Each of them is mapped with the same name of the detector itself.
  if(fDetectors) {
    for(std::map<std::string, HTDetector *>::iterator TheDetector=fDetectors->begin(); TheDetector!=fDetectors->end(); TheDetector++) {
      std::string DetectorName((*TheDetector).second->GetName());
      std::string DetectorType((*TheDetector).second->GetType());
      int NumIndividualDetectionObjects((*TheDetector).second->GetNumDetectors());
      if(DetectorType.compare("HTTDCSpare")==0) {
        HTTDCSpareMap * newMapping = new HTTDCSpareMap(DetectorName.c_str());
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTHiRA")==0) {
        HTHiRAMap * newMapping = new HTHiRAMap(DetectorName.c_str(), NumIndividualDetectionObjects);
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTNeutronWall")==0) {
        HTNeutronWallMap * newMapping = new HTNeutronWallMap(DetectorName.c_str(), NumIndividualDetectionObjects);
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTVetoWall")==0) {
        HTVetoWallMap * newMapping = new HTVetoWallMap(DetectorName.c_str(), NumIndividualDetectionObjects);
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTForwardArray")==0) {
        HTForwardArrayMap * newMapping = new HTForwardArrayMap(DetectorName.c_str(), NumIndividualDetectionObjects);
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTMicroball")==0) {
        HTMicroballMap * newMapping = new HTMicroballMap(DetectorName.c_str());
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      } else if(DetectorType.compare("HTSisTimestampe15190")==0) {
        HTSisTimestampe15190Map * newMapping = new HTSisTimestampe15190Map(DetectorName.c_str());
        newMapping->LoadMapping(gRun->GetMappingFile());
        (*fDetectorMaps)[DetectorName]=newMapping;
        (*TheDetector).second->SetMapping(newMapping);
      }
    }
  }
  return fDetectorMaps->size();
}

//________________________________________________
std::map<std::string, HTRootElectronics *> * HTExperimentalSetup::GetModules() const
{
  return fModules;
}

//________________________________________________
std::map<std::string, HTDetector *> * HTExperimentalSetup::GetDetectors() const
{
  return fDetectors;
}

//________________________________________________
HTRootElectronics * HTExperimentalSetup::GetModule(const char * name) const
{
  return (*fModules)[name];
}

//________________________________________________
HTRootElectronics * HTExperimentalSetup::GetModule(std::string name) const
{
  return (*fModules)[name];
}

//________________________________________________
HTDetector * HTExperimentalSetup::GetDetector(const char * name) const
{
  return (*fDetectors)[name];
}

//________________________________________________
HTDetector * HTExperimentalSetup::GetDetector(std::string name) const
{
  return (*fDetectors)[name];
}

//________________________________________________
int HTExperimentalSetup::GetNDetectors() const
{
  return fDetectors->size();
}

//________________________________________________
void HTExperimentalSetup::InitDetectorBranches(TTree * theTree)
{
  //Loop over all the define detectors to call their individual InitTTreeBranch(TTree *)
  if(fDetectors) {
    for(std::map<std::string, HTDetector *>::iterator TheDetector=fDetectors->begin(); TheDetector!=fDetectors->end(); TheDetector++) {
      (*TheDetector).second->InitTTreeBranch(theTree);
    }
  }
}
