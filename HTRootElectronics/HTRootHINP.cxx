#include <HTRootHINP.h>

//________________________________________________
HTRootHINP::HTRootHINP(const char * name) : HTRootElectronics(name),
fData(0)
{}

//________________________________________________
HTRootHINP::~HTRootHINP()
{
  if(fData) delete fData;
}

//________________________________________________
TTreeReaderValue<RBHINPHit> *  HTRootHINP::GetDataPointer() const
{
  return fData;
}
