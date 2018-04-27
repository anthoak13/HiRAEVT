#include <HTNeutronWall.h>

//________________________________________________
HTNeutronWall::HTNeutronWall(const char * name) : HTDetector(name),
fevt(0)
{
  fevt=new HTNeutronWallRootEvent();
  fType.assign("HTNeutronWall");
}

//________________________________________________
HTNeutronWall::~HTNeutronWall()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTNeutronWall::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTNeutronWallData",&(fevt->fNeutronWall),32768,1);
  return;
}

//________________________________________________
void HTNeutronWall::BuildEvent()
{
  //Retrieving information from HTRootModule types

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTNeutronWall::FillMappedData()
{

  return;
}
