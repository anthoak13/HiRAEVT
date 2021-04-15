#include <HTExperimentalSetup.h>

HTExperimentalSetup *HTExperimentalSetup::_instance = nullptr;

HTExperimentalSetup *HTExperimentalSetup::Instance()
{
   if (_instance == nullptr) {
      _instance = new HTExperimentalSetup();
   }

   return _instance;
}

//________________________________________________
HTExperimentalSetup::HTExperimentalSetup() : fModules(0), fDetectors(0)
{
   fModules = new std::map<std::string, HTRootElectronics *>;
   fDetectors = new std::map<std::string, HTDetector *>;
}

//________________________________________________
HTExperimentalSetup::~HTExperimentalSetup()
{
   if (fModules) {
      for (std::map<std::string, HTRootElectronics *>::iterator TheModule = fModules->begin();
           TheModule != fModules->end(); TheModule++) {
         delete (*TheModule).second;
      }
      delete fModules;
   }
   if (fDetectors) {
      for (std::map<std::string, HTDetector *>::iterator TheModule = fDetectors->begin();
           TheModule != fDetectors->end(); TheModule++) {
         delete (*TheModule).second;
      }
      delete fDetectors;
   }
}

//________________________________________________
int HTExperimentalSetup::BuildElectronicModules()
{
   // Definition of electronic modules to retrieve data from the ROOT Unpacked TTree
   for (int NumStack = 0; NumStack < HTExperimentInfo::Instance()->GetRunInfo()->GetNStacks(); NumStack++) {
      // Loop over all the defined stacks to retrieve individual module information
      HTDAQStackInfo *newStackInfo = HTExperimentInfo::Instance()->GetRunInfo()->GetStackInfo(NumStack);

      for (int NumModule = 0; NumModule < newStackInfo->GetNModules(); NumModule++) {
         // Loop over all the modules of a stack
         HTModuleInfo *newModuleInfo = newStackInfo->GetModuleInfo(NumModule);
         std::string newModuleType(newModuleInfo->GetModuleType());
         std::string newModuleName(newModuleInfo->GetModuleName());

         if (newModuleType.compare("HTSisTimestampUnpacker") == 0) {
            HTRootSisTimestamp *newModule = new HTRootSisTimestamp(newModuleName.c_str());
            (*fModules)[newModuleName] = newModule;

         } else if (newModuleType.compare("HTTimestamp") == 0) {
            HTRootTimestamp *newModule = new HTRootTimestamp(newModuleName.c_str());
            (*fModules)[newModuleName] = newModule;

         } else if (newModuleType.compare("HTHINPUnpacker") == 0) {
            HTRootHINP *newModule = new HTRootHINP(newModuleName.c_str());
            (*fModules)[newModuleName] = newModule;

         } else if (newModuleType.compare("HTCAEN7xxUnpacker") == 0) {
            HTRootCAEN7xx *newModule = new HTRootCAEN7xx(newModuleName.c_str());
            int LineLoaded = newModule->LoadPedestals(HTExperimentInfo::Instance()->GetRunInfo()->GetPedestalFile());
            if (LineLoaded < 0) {
               printf("HTRootCAEN7xx: Error while loading pedestal file %s\n",
                      HTExperimentInfo::Instance()->GetRunInfo()->GetPedestalFile());
            } else {
               printf("HTRootCAEN7xx: Module %s has loaded %d lines from pedestal file %s\n", newModuleName.c_str(),
                      LineLoaded, HTExperimentInfo::Instance()->GetRunInfo()->GetPedestalFile());
            }
            (*fModules)[newModuleName] = newModule;

         } else if (newModuleType.compare("HTCAEN1x90Unpacker") == 0) {
            HTRootCAEN1x90 *newModule = new HTRootCAEN1x90(newModuleName.c_str(), newModuleInfo->GetNumCh());
            (*fModules)[newModuleName] = newModule;
         } else if (newModuleType.compare("HTMADC32Unpacker") == 0) {
            HTRootMADC32 *newModule = new HTRootMADC32(newModuleName.c_str());
            (*fModules)[newModuleName] = newModule;
         } else {
            std::cerr << newModuleType << " is not a known module (no corresponding HTRoot class)" << std::endl;
         }
      }
   }
   return fModules->size();
}

//________________________________________________
int HTExperimentalSetup::BuildDetectors()
{
   std::ifstream FileIn(HTExperimentInfo::Instance()->GetRunInfo()->GetMappingFile());
   if (!FileIn.is_open()) {
      printf("HTExperimentalSetup: Failed to build detectors, error while opening %s file\n",
             HTExperimentInfo::Instance()->GetRunInfo()->GetMappingFile());
      return -1;
   }

   while (!FileIn.eof()) {
      std::string LineRead;
      std::getline(FileIn, LineRead);
      std::string LineReadCommentLess(LineRead.substr(0, LineRead.find("*")));

      if (LineReadCommentLess.empty())
         continue;

      if (LineReadCommentLess.find_first_not_of(' ') == std::string::npos)
         continue;

      if (LineReadCommentLess.find("define ") != std::string::npos)
         ParseDefineMappingLine(LineReadCommentLess.c_str());

      else if (LineReadCommentLess.find("assign ") != std::string::npos)
         ParseAssignMappingLine(LineReadCommentLess.c_str());
   }
   FileIn.close();

   printf("HTExperimentalSetup: Built %lu detectors from file %s\n", fDetectors->size(),
          HTExperimentInfo::Instance()->GetRunInfo()->GetMappingFile());
   return fDetectors->size();
}

//________________________________________________
int HTExperimentalSetup::ParseDefineMappingLine(const char *line_to_parse)
{
   std::string LineReadCommentLess(line_to_parse);

   int NDets = fDetectors->size();

   if (LineReadCommentLess.find("detector ") != std::string::npos) {
      LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("detector ") + 9));

      std::istringstream LineStream(LineReadCommentLess);
      std::string DetectorType;
      std::string DetectorName;
      int numDets;

      // Load in the detector information
      LineStream >> DetectorType >> DetectorName >> numDets;

      DetectorName.assign(DetectorName.substr(DetectorName.find("\"") + 1,
                                              DetectorName.find_last_of("\"") - (DetectorName.find("\"") + 1)));

      (*fDetectors)[DetectorName] = HTDetectorFactory::Instance()->CreateDetector(DetectorType, DetectorName, numDets);

   } // End if statment that detector line exists

   return fDetectors->size() - NDets;
}

//________________________________________________
int HTExperimentalSetup::ParseAssignMappingLine(const char *line_to_parse)
{
   int NModulesAdded = 0;

   std::string LineReadCommentLess(line_to_parse);
   if (LineReadCommentLess.find("module ") != std::string::npos) {
      LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("module ") + 7));
      std::istringstream LineStream(LineReadCommentLess);
      std::string DetectorName;
      LineStream >> DetectorName;
      std::string ModuleName;

      while (LineStream >> ModuleName) {
         if (fDetectors->find(DetectorName) != fDetectors->end()) {
            NModulesAdded++;
            //(*fDetectors)[DetectorName]->AssignModule((*fModules)[ModuleName]);
         } else
            throw std::invalid_argument(DetectorName.append(" not defined!"));
      }
   }

   return NModulesAdded;
}

//________________________________________________
void HTExperimentalSetup::BuildDetectorMaps()
{
   // Loop over the defined detectors to build the corresponding detector mappers
   // Each of them is mapped with the same name of the detector itself.
   int nMappedLines = 0;
   for (auto &&det : *fDetectors)
      ; // nMappedLines += det.second->LoadMapping(HTExperimentInfo::Instance()->GetRunInfo()->GetMappingFile());
}

//________________________________________________
std::map<std::string, HTRootElectronics *> *HTExperimentalSetup::GetModules() const
{
   return fModules;
}

//________________________________________________
std::map<std::string, HTDetector *> *HTExperimentalSetup::GetDetectors() const
{
   return fDetectors;
}

//________________________________________________
HTRootElectronics *HTExperimentalSetup::GetModule(const char *name) const
{
   return (*fModules)[name];
}

//________________________________________________
HTRootElectronics *HTExperimentalSetup::GetModule(std::string name) const
{
   return (*fModules)[name];
}

//________________________________________________
HTDetector *HTExperimentalSetup::GetDetector(const char *name) const
{
   return (*fDetectors)[name];
}

//________________________________________________
HTDetector *HTExperimentalSetup::GetDetector(std::string name) const
{
   return (*fDetectors)[name];
}

//________________________________________________
int HTExperimentalSetup::GetNDetectors() const
{
   return fDetectors->size();
}

//________________________________________________
void HTExperimentalSetup::InitDetectorBranches(TTree *theTree)
{
   // Loop over all the define detectors to call their individual InitTTreeBranch(TTree *)
   if (fDetectors) {
      for (std::map<std::string, HTDetector *>::iterator TheDetector = fDetectors->begin();
           TheDetector != fDetectors->end(); TheDetector++) {
         ; //(*TheDetector).second->InitTTreeBranch(theTree);
      }
   }
}
