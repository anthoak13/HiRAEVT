#include <HTRootHINP.h>

//________________________________________________
HTRootHINP::HTRootHINP(const char *name) : HTRootElectronics(name), fData(0) {}

//________________________________________________
HTRootHINP::~HTRootHINP()
{
   if (fData)
      delete fData;
}

//________________________________________________
TTreeReaderValue<HTHINPHit> *HTRootHINP::GetDataPointer() const
{
   return fData;
}

void HTRootHINP::InitTreeInputBranch(TTreeReader &theReader)
{
   fData = new TTreeReaderValue<HTHINPHit>(theReader, Form("%s.", GetName()));
}
