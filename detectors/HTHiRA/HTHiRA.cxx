#include <HTHiRA.h>

//________________________________________________
HTHiRA::HTHiRA(const char * name, int num_telescopes) : HTDetector(name, num_telescopes),
fevt(0)
{
  fevt=new HTHiRARootEvent(fNumDetectors);
  fType.assign("HTHiRA");
}

//________________________________________________
HTHiRA::~HTHiRA()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTHiRA::Clear()
{

}


//________________________________________________
void HTHiRA::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTHiRAData",&(fevt->fHiRA),32768,3);
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
