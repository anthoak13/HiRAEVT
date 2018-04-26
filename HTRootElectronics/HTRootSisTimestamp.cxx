#include <HTRootSisTimestamp.h>

//________________________________________________
HTRootSisTimestamp::HTRootSisTimestamp(const char * name) : HTRootElectronics(name),
fTimestamp(0),
fTimestampKoreans(0)
{}

//________________________________________________
HTRootSisTimestamp::~HTRootSisTimestamp()
{
  if(fTimestamp) delete fTimestamp;
  if(fTimestampKoreans) delete fTimestampKoreans;
}

void HTRootSisTimestamp::InitTreeInputBranch(TTreeReader& theReader)
{
  fTimestamp = new TTreeReaderValue<Long64_t>(theReader, GetName());
  fTimestampKoreans = new TTreeReaderValue<Long64_t>(theReader, Form("%s%s",GetName(),"Koreans"));
}

Long64_t HTRootSisTimestamp::GetData() const
{
  return *(*fTimestamp);
}

Long64_t HTRootSisTimestamp::GetDataKoreans() const
{
  return *(*fTimestampKoreans);
}
