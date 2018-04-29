#include <HTMicroball.h>

/* WARNING: uBall number of rings and detectors per ring is fixed */
const int N_RINGS = 9;
const int N_DETS[] = {6, 10, 12, 12, 14, 14, 12, 10, 6};
// Detector numbering within a ring starts from 1 but the arrays start from 0
/******************************************************************/

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
void HTMicroball::Clear()
{

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
