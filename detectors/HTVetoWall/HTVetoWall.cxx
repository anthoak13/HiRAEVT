#include <HTVetoWall.h>

//________________________________________________
HTVetoWall::HTVetoWall(const char * name) : HTDetector(name),
fevt(0)
{
  fevt=new HTVetoWallRootEvent();
  fType.assign("HTVetoWall");
}

//________________________________________________
HTVetoWall::~HTVetoWall()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTVetoWall::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTVetoWallData",&(fevt->fVetoWall),32768,2);
  return;
}

//________________________________________________
void HTVetoWall::BuildEvent()
{
  //Retrieving information from HTRootModule types

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTVetoWall::FillMappedData()
{

  return;
}
