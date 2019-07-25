#include <HTSisTimestampe15190.h>

#define dModuleTimestamp ((HTSisTimestampe15190Map *)fDetectorMapping)->GetTimestampModule()
#define dModuleTimestampKoreans ((HTSisTimestampe15190Map *)fDetectorMapping)->GetTimestampKoreansModule()

//________________________________________________
HTSisTimestampe15190::HTSisTimestampe15190(const char * name) : HTDetector(name),
fevt(0)
{
  fevt=new HTTSe15190RootEvent();
  fType.assign("HTSisTimestampe15190");
}

//________________________________________________
HTSisTimestampe15190::~HTSisTimestampe15190()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTSisTimestampe15190::Clear()
{}

//________________________________________________
void HTSisTimestampe15190::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTTSe15190Data",&(fevt->fSisTimestamp),32768,1);
  return;
}

//________________________________________________
void HTSisTimestampe15190::BuildEvent()
{
  //Clear detector
  //Clear();

  //Retrieving information from HTRootModule types
  fTimestamp=dModuleTimestamp >=0 ? ((HTRootSisTimestamp*)fModules[dModuleTimestamp])->GetData() : -9999;
  fTimestampKoreans=dModuleTimestampKoreans >=0 ? ((HTRootSisTimestamp*)fModules[dModuleTimestampKoreans])->GetData() : -9999;

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTSisTimestampe15190::FillMappedData()
{
  (fevt->fSisTimestamp).fTimestamp=fTimestamp;
  (fevt->fSisTimestamp).fTimestampKoreans=fTimestampKoreans;
  return;
}

void HTSisTimestampe15190::InitMapping()
{
  fDetectorMapping = new HTSisTimestampe15190Map(fName);
}
