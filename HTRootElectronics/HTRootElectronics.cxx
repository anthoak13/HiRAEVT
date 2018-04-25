#include <HTRootElectronics.h>

//________________________________________________
HTRootElectronics::HTRootElectronics(const char * name) :
fName(name)
{}

//________________________________________________
HTRootElectronics::~HTRootElectronics()
{}

//________________________________________________
void * HTRootElectronics::GetDataPointer() const
{
  return 0;
}

//________________________________________________
const char * HTRootElectronics::GetName() const
{
  return fName;
}
