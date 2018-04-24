#include <HTDetector.h>

//________________________________________________
HTDetector::HTDetector() :
fDetectorMapping(0)
{}

//________________________________________________
HTDetector::~HTDetector()
{
  if(fDetectorMapping) delete fDetectorMapping;
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
