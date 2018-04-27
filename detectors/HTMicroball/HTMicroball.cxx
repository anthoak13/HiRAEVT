#include <HTMicroball.h>

//________________________________________________
HTMicroball::HTMicroball(const char * name) : HTDetector(name),
fevt(0)
{
  fevt=new HTMicroballRootEvent();
  fType.assign("HTMicroball");
}

//________________________________________________
HTMicroball::~HTMicroball()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTMicroball::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTMicroballData",&(fevt->fMicroball),32768,1);
  return;
}

//________________________________________________
void HTMicroball::BuildEvent()
{
  //Retrieving information from HTRootModule types

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTMicroball::FillMappedData()
{

  return;
}
