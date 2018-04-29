#include <HTDetector.h>

//________________________________________________
HTDetector::HTDetector(const char * name, int num_detectors) :
fName(name),
fNumDetectors(num_detectors),
fDetectorMapping(0)
{}

//________________________________________________
HTDetector::~HTDetector()
{
  if(fDetectorMapping) delete fDetectorMapping;
}

//________________________________________________
void HTDetector::Clear()
{
  return;
}

//________________________________________________
void HTDetector::AssignModule(HTRootElectronics * newModule)
{
  fModules.push_back(newModule);
}

//________________________________________________
void HTDetector::SetMapping(HTDetectorMap * detMapping)
{
  fDetectorMapping=detMapping;
}

//________________________________________________
const char * HTDetector::GetName() const
{
  return fName.c_str();
}

//________________________________________________
const char * HTDetector::GetType() const
{
  return fType.c_str();
}

//________________________________________________
int HTDetector::GetNumDetectors() const
{
  return fNumDetectors;
}

//________________________________________________
void HTDetector::InitTTreeBranch(TTree * theTree)
{
  return;
}

//________________________________________________
void HTDetector::BuildEvent()
{
  return;
}

//________________________________________________
void HTDetector::FillMappedData()
{
  return;
}
