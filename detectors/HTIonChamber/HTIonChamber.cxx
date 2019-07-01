#include <HTIonChamber.h>

#define dModuleEnergy(det) ((HTIonChamberMap *)fDetectorMapping)->GetEnergyModule(det)
#define dChannelEnergy(det) ((HTIonChamberMap *)fDetectorMapping)->GetEnergyChannel(det)
#define dModuleTime(det) ((HTIonChamberMap *)fDetectorMapping)->GetTimeModule(det)
#define dChannelTime(det) ((HTIonChamberMap *)fDetectorMapping)->GetTimeChannel(det)

//________________________________________________
HTIonChamber::HTIonChamber(const char * name, int num_detectors) : HTDetector(name, num_detectors),
fIonChamber(0),
fevt(0)
{
  fIonChamber=new HTIonChamberCluster(fNumDetectors);
  fevt=new HTIonChamberRootEvent(fNumDetectors);
  fType.assign("HTIonChamber");
}

//________________________________________________
HTIonChamber::~HTIonChamber()
{
  if(fIonChamber) delete fIonChamber;
  if(fevt) delete fevt;
}

//________________________________________________
void HTIonChamber::Clear()
{}

//________________________________________________
void HTIonChamber::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTIonChamberData",&(fevt->fIonChamber),32768,1);
  return;
}

//________________________________________________
void HTIonChamber::BuildEvent()
{
  //Retrieving information from HTRootModule types
  for(int NumDet=0; NumDet<fNumDetectors; NumDet++) {
    fIonChamber->GetDetector(NumDet)->SetE(dModuleEnergy(NumDet)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleEnergy(NumDet)])->GetData(dChannelEnergy(NumDet)) : -9999);
    fIonChamber->GetDetector(NumDet)->SetTime(dModuleTime(NumDet)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTime(NumDet)])->GetData(dChannelTime(NumDet)) : -9999);
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTIonChamber::FillMappedData()
{
  //Retrieving information from HTIonChamberCluster to fill HTIonChamberData object
  fevt->fIonChamber.fmulti=0;
  for(int NumDet=0; NumDet<fNumDetectors; NumDet++) {
    HTIonChamberDetector * DetToFill = fIonChamber->GetDetector(NumDet);
    if(DetToFill->GetE()>0 && DetToFill->GetTime()!=-9999)
    {
      fevt->fIonChamber.fnumdet[fevt->fIonChamber.fmulti]=NumDet+1; //WARNING: detectors are counted from 1 in the FA experimental configuration
      fevt->fIonChamber.fE[fevt->fIonChamber.fmulti]=DetToFill->GetE();
      fevt->fIonChamber.fTime[fevt->fIonChamber.fmulti]=DetToFill->GetTime();
      fevt->fIonChamber.fmulti++;
    }
  }

  return;
}
