#include <HTRootSisTimestamp.h>

//________________________________________________
HTRootSisTimestamp::HTRootSisTimestamp(TString name) : HTRootModule(name)
{
   Clear();
}

//________________________________________________
HTRootSisTimestamp::~HTRootSisTimestamp() {}

void HTRootSisTimestamp::Clear()
{
   fData[0] = 0;
   fData[1] = 0;
}
ClassImp(HTRootSisTimestamp)
