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
  return;
}

//________________________________________________
void HTSisTimestampe15190::BuildEvent()
{
  return;
}

//________________________________________________
void HTSisTimestampe15190::FillMappedData()
{
  return;
}
