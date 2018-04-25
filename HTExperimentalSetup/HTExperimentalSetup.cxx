#include <HTExperimentalSetup.h>

//________________________________________________
HTExperimentalSetup::HTExperimentalSetup()
{}

//________________________________________________
HTExperimentalSetup::~HTExperimentalSetup()
{}

//________________________________________________
int HTExperimentalSetup::BuildElectronicModules()
{
  return fModules.size();
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
HTRootElectronics * HTExperimentalSetup::GetModule(const char * name) const
{
  for(unsigned int i=0; i<fModules.size(); i++) {
    if(strcmp(name,fModules[i]->GetName())==0) return fModules[i];
  }
  return 0; //Module name not among registered modules
}

//________________________________________________
HTRootElectronics * HTExperimentalSetup::GetModule(int modnumer) const
{
  return fModules[modnumer];
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
