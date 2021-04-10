#include <HTRootSisTimestamp.h>

//________________________________________________
HTRootSisTimestamp::HTRootSisTimestamp(const char *name) : HTRootElectronics(name), fTimestamp(0) {}

//________________________________________________
HTRootSisTimestamp::~HTRootSisTimestamp()
{
   if (fTimestamp)
      delete fTimestamp;
}

void HTRootSisTimestamp::InitTreeInputBranch(TTreeReader &theReader)
{
   fTimestamp = new TTreeReaderArray<ULong64_t>(theReader, GetName());
}

ULong64_t HTRootSisTimestamp::GetData(int ch) const
{
   return (*fTimestamp)[ch];
}
