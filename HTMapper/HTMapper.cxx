#include <HTMapper.h>

//________________________________________________
HTMapper::HTMapper() : fMappedTree(0), fFileOut(0), fRunNumber(-1) {}

//________________________________________________
HTMapper::~HTMapper() {}

//________________________________________________
int HTMapper::PassArguments(int argc, char **argv)
{
   // Find the --run cmd argument and extract run number
   for (int i = 1; i < argc; i++) {
      std::string Argument(argv[i]);
      if (Argument.find("--run=") != std::string::npos) {
         fRunNumber = std::stoi(Argument.substr(Argument.find("--run=") + 6));
      }
   }

   if (fRunNumber < 0)
      return -1;
   return 0;
}

//________________________________________________
int HTMapper::InitializeMapper(const char *file_config_name)
{
   // Loading configuration file and building RunInfo
   if (LoadExperimentInfo(file_config_name) != 0)
      return -3;

   // Building Experimental Setup
   if (BuildExperimentalSetup() != 0)
      return -1;

   // Initializing output TFile and TTree
   if (InitRootOutput() != 0)
      return -2;

   return 0;
}

//________________________________________________
int HTMapper::LoadExperimentInfo(const char *file_name)
{
   // Initialization of HTRunInfo class
   std::cout << "** Initializing Run Info **\n";
   std::cout << "Loading config file: " << file_name << std::endl;

   if (HTExperimentInfo::Instance()->InitClass(file_name) <= 0) {
      std::cout << "Error while reading configuration file.\n";
      exit(-1);
   }

   auto runInfo = HTExperimentInfo::Instance()->SetRunNumber(fRunNumber);
   std::cout << "** Run Info correctly initialized **\n" << std::endl;

   return 0;
}

//________________________________________________
int HTMapper::BuildExperimentalSetup()
{

   if (HTExperimentalSetup::Instance() == 0)
      return -1;

   if (HTExperimentalSetup::Instance()->BuildElectronicModules() <= 0)
      return -2;
   std::cout << "Electronic modules initialized" << std::endl;

   if (HTExperimentalSetup::Instance()->BuildDetectors() <= 0)
      return -3;
   std::cout << "Detectors initialized" << std::endl;

   HTExperimentalSetup::Instance()->BuildDetectorMaps();
   std::cout << "Detectors mapped" << std::endl;

   return 0;
}

//________________________________________________
int HTMapper::InitRootOutput()
{
   // Opening a new TFile for output
   fFileOut =
      new TFile(Form("%srun-%04d.root", HTExperimentInfo::Instance()->GetMappedRootFilePath(), fRunNumber), "RECREATE");
   if (fFileOut->IsZombie())
      return -1; // failed to open TFile

   // Creating output TTree
   fMappedTree = new TTree(Form("E%s", HTExperimentInfo::Instance()->GetName()),
                           HTExperimentInfo::Instance()->GetRunInfo()->GetTitle(), 2);

   fMappedTree->SetAutoSave(50000000);

   // call individual detectors InitTTreeBranch
   HTExperimentalSetup::Instance()->InitDetectorBranches(fMappedTree);

   printf("HTMapper: Opened ROOT file %s\n",
          Form("%srun-%04d.root", HTExperimentInfo::Instance()->GetMappedRootFilePath(), fRunNumber));

   return 0;
}

//________________________________________________
TTree *HTMapper::GetMappedTree() const
{
   return fMappedTree;
}

//________________________________________________
void HTMapper::EndMapping()
{
   // Writing TTree to file and close file
   fMappedTree->AutoSave();
   fMappedTree->GetCurrentFile()->Close();

   return;
}

//________________________________________________
void HTMapper::MapDetectors()
{
   // Loop over the defined detectors to call their individual HTDetector::BuildEvent()
   auto DefinedDetectors = HTExperimentalSetup::Instance()->GetDetectors();

   for (auto TheDetector : *DefinedDetectors)
      TheDetector.second->BuildEvent();

   return;
}

//________________________________________________
void HTMapper::FillMappedEvent()
{
   // Calling TTree::Fill() with mapped data
   fMappedTree->Fill();

   return;
}
