#include <HTForwardArray.h>

//________________________________________________
HTForwardArray::HTForwardArray(const char * name, int num_detectors) : HTDetector(name, num_detectors),
fForwardArray(0),
fevt(0)
{
  fForwardArray=new HTForwardArrayCluster(fNumDetectors);
  fevt=new HTForwardArrayRootEvent(fNumDetectors);
  fType.assign("HTForwardArray");
}

//________________________________________________
HTForwardArray::~HTForwardArray()
{
  if(fForwardArray) delete fForwardArray;
  if(fevt) delete fevt;
}

//________________________________________________
void HTForwardArray::Clear()
{}

//________________________________________________
void HTForwardArray::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTForwardArrayData",&(fevt->fForwardArray),32768,1);
  return;
}

//________________________________________________
void HTForwardArray::BuildEvent()
{
  //Retrieving information from HTRootModule types

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTForwardArray::FillMappedData()
{

  return;
}
