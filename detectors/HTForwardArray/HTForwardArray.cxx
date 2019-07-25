#include <HTForwardArray.h>

#define dModuleEnergy(det) ((HTForwardArrayMap *)fDetectorMapping)->GetEnergyModule(det)
#define dChannelEnergy(det) ((HTForwardArrayMap *)fDetectorMapping)->GetEnergyChannel(det)
#define dModuleTime(det) ((HTForwardArrayMap *)fDetectorMapping)->GetTimeModule(det)
#define dChannelTime(det) ((HTForwardArrayMap *)fDetectorMapping)->GetTimeChannel(det)

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
  for(int NumDet=0; NumDet<fNumDetectors; NumDet++) {
    fForwardArray->GetDetector(NumDet)->SetE(dModuleEnergy(NumDet)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleEnergy(NumDet)])->GetData(dChannelEnergy(NumDet)) : -9999);
    fForwardArray->GetDetector(NumDet)->SetTime(dModuleTime(NumDet)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTime(NumDet)])->GetData(dChannelTime(NumDet)) : -9999);
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTForwardArray::FillMappedData()
{
  //Retrieving information from HTForwardArrayCluster to fill HTForwardArrayData object
  fevt->fForwardArray.fmulti=0;
  for(int NumDet=0; NumDet<fNumDetectors; NumDet++) {
    HTForwardArrayDetector * DetToFill = fForwardArray->GetDetector(NumDet);
    if(DetToFill->GetE()>0 && DetToFill->GetTime()!=-9999)
    {
      fevt->fForwardArray.fnumdet[fevt->fForwardArray.fmulti]=NumDet+1; //WARNING: detectors are counted from 1 in the FA experimental configuration
      fevt->fForwardArray.fE[fevt->fForwardArray.fmulti]=DetToFill->GetE();
      fevt->fForwardArray.fTime[fevt->fForwardArray.fmulti]=DetToFill->GetTime();
      fevt->fForwardArray.fmulti++;
    }
  }

  return;
}

void HTForwardArray::InitMapping()
{
  fDetectorMapping = new HTForwardArrayMap(fName, fNumDetectors);
}
