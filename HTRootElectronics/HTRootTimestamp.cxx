#include <HTRootTimestamp.h>

//________________________________________________
HTRootTimestamp::HTRootTimestamp(const char * name) : HTRootElectronics(name),
fTimestamp(0)
{}

//________________________________________________
HTRootTimestamp::~HTRootTimestamp()
{
  if(fTimestamp) delete fTimestamp;
}

void HTRootTimestamp::InitTreeInputBranch(TTreeReader& theReader)
{
  fTimestamp = new TTreeReaderValue<Long64_t>(theReader, GetName());
}

Long64_t HTRootTimestamp::GetData() const
{
  return *(*fTimestamp);
}
