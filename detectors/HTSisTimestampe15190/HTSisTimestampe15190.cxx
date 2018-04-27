#include <HTSisTimestampe15190.h>

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
void HTSisTimestampe15190::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTTSe15190Data",&(fevt->fSisTimestamp),32768,1);
  return;
}

//________________________________________________
void HTSisTimestampe15190::BuildEvent()
{
  //Retrieving information from HTRootModule types
  fTimestamp=((HTRootSisTimestamp*)fModules[((HTSisTimestampe15190Map *)fDetectorMapping)->GetTimestampModule()])->GetData();
  fTimestampKoreans=((HTRootSisTimestamp*)fModules[((HTSisTimestampe15190Map *)fDetectorMapping)->GetTimestampKoreansModule()])->GetData();

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
