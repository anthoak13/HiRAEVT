#include <HTRootElectronics.h>

//________________________________________________
HTRootElectronics::HTRootElectronics(const char *name) : fName(name) {}

//________________________________________________
HTRootElectronics::HTRootElectronics() {}

//________________________________________________
HTRootElectronics::~HTRootElectronics() {}

//________________________________________________
const char *HTRootElectronics::GetName() const
{
   return fName.c_str();
}

//________________________________________________
void HTRootElectronics::InitTreeOutputBranch(TTree *theTree) const
{
   return;
}

//________________________________________________
void HTRootElectronics::InitTreeInputBranch(TTreeReader &theReader)
{
   return;
}
