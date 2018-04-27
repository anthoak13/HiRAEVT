#include <HTHiRA.h>

//________________________________________________
HTHiRA::HTHiRA(const char * name) : HTDetector(name),
fevt(0)
{
  fevt=new HTHiRARootEvent();
  fType.assign("HTHiRA");
}

//________________________________________________
HTHiRA::~HTHiRA()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTHiRA::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTHiRAData",&(fevt->fHiRA),32768,1);
  return;
}

//________________________________________________
void HTHiRA::BuildEvent()
{
  //Retrieving information from HTRootModule types

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTHiRA::FillMappedData()
{

  return;
}
