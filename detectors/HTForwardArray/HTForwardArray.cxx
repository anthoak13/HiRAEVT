#include <HTForwardArray.h>

//________________________________________________
HTForwardArray::HTForwardArray(const char * name, int num_detectors) : HTDetector(name, num_detectors),
fevt(0)
{
  fevt=new HTForwardArrayRootEvent(fNumDetectors);
  fType.assign("HTForwardArray");
}

//________________________________________________
HTForwardArray::~HTForwardArray()
{
  if(fevt) delete fevt;
}

//________________________________________________
void HTForwardArray::Clear()
{

}

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
