#include <HTMapper.h>

//________________________________________________
HTMapper::HTMapper() :
fMappedTree(0),
fFileOut(0),
fRunNumber(-1)
{}

//________________________________________________
HTMapper::~HTMapper()
{}

//________________________________________________
int HTMapper::PassArguments(int argc, char** argv)
{
  // Find the --run cmd argument and extract run number
  for(int i=1; i<argc; i++)
  {
    std::string Argument(argv[i]);
    if(Argument.find("--run=")!=std::string::npos) {
      fRunNumber=std::stoi(Argument.substr(Argument.find("--run=")+6));
    }
  }

  if(fRunNumber<0) return -1;
  return 0;
}

//________________________________________________
int HTMapper::InitializeMapper(const char * file_config_name)
{
  //Loading configuration file and building RunInfo
  if(LoadExperimentInfo(file_config_name)!=0)
    return -3;


  //Building Experimental Setup
  if(BuildExperimentalSetup()!=0)
    return -1;

  //Initializing output TFile and TTree
  if(InitRootOutput()!=0)
    return -2;

  return 0;
}

//________________________________________________
int HTMapper::LoadExperimentInfo(const char * file_name)
{
  //Initialization of RBRunInfo class
  std::cout << "** Initializing Run Info **\n";
  std::cout << "Loading config file: " << file_name << std::endl;

  gExperimentInfo = new HTExperimentInfo();

  if(gExperimentInfo->InitClass(file_name)<=0) {
    std::cout << "Error while reading configuration file.\n";
    exit (-1);
  }
  
  gRun=gExperimentInfo->GetRunInfo(fRunNumber);
  if(gRun==0) {
   std::cout << "Failed to get run info." << std::endl;
   exit(-1);
  }

  std::cout << "** Run Info correctly initialized **\n";

  return 0;
}

//________________________________________________
int HTMapper::BuildExperimentalSetup()
{


  if(HTExperimentalSetup::Instance()==0)
    return -1;

  if(HTExperimentalSetup::Instance()->BuildElectronicModules()<=0)
    return -2;
  std::cout << "Electronic modules initialized" << std::endl;
  
  if(HTExperimentalSetup::Instance()->BuildDetectors()<=0)
    return -3;
  std::cout << "Detectors initialized" << std::endl;
  
  std::cout << "Detectors mapped" << std::endl;
  
  return 0;
}

//________________________________________________
int HTMapper::InitRootOutput()
{
  // Opening a new TFile for output
  fFileOut = new TFile(Form("%srun-%04d.root", gExperimentInfo->GetMappedRootFilePath(), fRunNumber), "RECREATE");
  if(fFileOut->IsZombie()) return -1; //failed to open TFile

  // Creating output TTree
  fMappedTree = new TTree(Form("E%s",gExperimentInfo->GetName()), gRun->GetTitle(),2);
  fMappedTree->SetAutoSave(50000000);

  //call individual detectors InitTTreeBranch
  HTExperimentalSetup::Instance()->InitDetectorBranches(fMappedTree);

  printf("HTMapper: Opened ROOT file %s\n", Form("%srun-%04d.root", gExperimentInfo->GetMappedRootFilePath(), fRunNumber));

  return 0;
}

//________________________________________________
TTree * HTMapper::GetMappedTree() const
{
  return fMappedTree;
}

//________________________________________________
void HTMapper::EndMapping()
{
  //Writing TTree to file and close file
  fMappedTree->AutoSave();
  fMappedTree->GetCurrentFile()->Close();

  return;
}

//________________________________________________
void HTMapper::MapDetectors()
{
  //Loop over the defined detectors to call their individual HTDetector::BuildEvent()
  std::map<std::string, HTDetector *> * DefinedDetectors = HTExperimentalSetup::Instance()->GetDetectors();
  for(std::map<std::string, HTDetector *>::iterator TheDetector=DefinedDetectors->begin(); TheDetector!=DefinedDetectors->end(); TheDetector++)
  {
    (TheDetector)->second->BuildEvent();
  }

  return;
}

//________________________________________________
void HTMapper::FillMappedEvent()
{
  //Calling TTree::Fill() with mapped data
  fMappedTree->Fill();

  return;
}
