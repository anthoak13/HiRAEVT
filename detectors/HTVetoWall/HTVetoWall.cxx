#include <HTVetoWall.h>

//________________________________________________
HTVetoWall::HTVetoWall(const char * name, int num_bars) : HTDetector(name, num_bars),
fVetoWall(0),
fevt(0)
{
  fVetoWall=new HTVetoWallArray(fNumDetectors);
  fevt=new HTVetoWallRootEvent(fNumDetectors);
  fType.assign("HTVetoWall");
}

//________________________________________________
HTVetoWall::~HTVetoWall()
{
  if(fVetoWall) delete fVetoWall;
  if(fevt) delete fevt;
}

//________________________________________________
void HTVetoWall::Clear()
{

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
