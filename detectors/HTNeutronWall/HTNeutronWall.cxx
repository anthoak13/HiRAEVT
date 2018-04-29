#include <HTNeutronWall.h>

#define dModuleLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetLeftModule(bar)
#define dChannelLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetLeftChannel(bar)
#define dModuleRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetRightModule(bar)
#define dChannelRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetRightChannel(bar)
#define dModuleFastLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetFastLeftModule(bar)
#define dChannelFastLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetFastLeftChannel(bar)
#define dModuleFastRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetFastRightModule(bar)
#define dChannelFastRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetFastRightChannel(bar)
#define dModuleTimeLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetTimeLeftModule(bar)
#define dChannelTimeLeft(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetTimeLeftChannel(bar)
#define dModuleTimeRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetTimeRightModule(bar)
#define dChannelTimeRight(bar) ((HTNeutronWallMap *)fDetectorMapping)->GetTimeRightChannel(bar)

//________________________________________________
HTNeutronWall::HTNeutronWall(const char * name, int num_bars) : HTDetector(name, num_bars),
fNeutronWall(0),
fevt(0)
{
  fNeutronWall=new HTNeutronWallArray(fNumDetectors);
  fevt=new HTNeutronWallRootEvent(fNumDetectors);
  fType.assign("HTNeutronWall");
}

//________________________________________________
HTNeutronWall::~HTNeutronWall()
{
  if(fNeutronWall) delete fNeutronWall;
  if(fevt) delete fevt;
}

//________________________________________________
void HTNeutronWall::Clear()
{

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
  for(int NumBar=0; NumBar<fNumDetectors; NumBar++) {
    fNeutronWall->GetBar(NumBar)->SetAnodeCommonLeft(dModuleLeft(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleLeft(NumBar)])->GetData(dChannelLeft(NumBar)) : -9999);
    fNeutronWall->GetBar(NumBar)->SetAnodeCommonRight(dModuleRight(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleRight(NumBar)])->GetData(dChannelRight(NumBar)) : -9999);
    fNeutronWall->GetBar(NumBar)->SetAnodeIndividualLeft(dModuleFastLeft(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleFastLeft(NumBar)])->GetData(dChannelFastLeft(NumBar)) : -9999);
    fNeutronWall->GetBar(NumBar)->SetAnodeIndividualRight(dModuleFastRight(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleFastRight(NumBar)])->GetData(dChannelFastRight(NumBar)) : -9999);
    fNeutronWall->GetBar(NumBar)->SetTimeLeft(dModuleTimeLeft(NumBar)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTimeLeft(NumBar)])->GetData(dChannelTimeLeft(NumBar)) : -9999);
    fNeutronWall->GetBar(NumBar)->SetTimeRight(dModuleTimeRight(NumBar)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTimeRight(NumBar)])->GetData(dChannelTimeRight(NumBar)) : -9999);
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTNeutronWall::FillMappedData()
{
  //Retrieving information from HTNeutronWallArray to fill HTNeutronWallRootEvent object
  fevt->fNeutronWall.fmulti=0;
  for(int NumBar=0; NumBar<fNumDetectors; NumBar++) {
    HTNeutronWallBar * BarToFill = fNeutronWall->GetBar(NumBar);
    if(BarToFill->GetAnodeCommonLeft()>0 && BarToFill->GetAnodeCommonRight()>0 && BarToFill->GetTimeLeft()!=-9999 && BarToFill->GetTimeRight()!=-9999)
    {
      fevt->fNeutronWall.fnumbar[fevt->fNeutronWall.fmulti]=NumBar;
      fevt->fNeutronWall.fLeft[fevt->fNeutronWall.fmulti]=BarToFill->GetAnodeCommonLeft();
      fevt->fNeutronWall.fRight[fevt->fNeutronWall.fmulti]=BarToFill->GetAnodeCommonRight();
      fevt->fNeutronWall.ffastLeft[fevt->fNeutronWall.fmulti]=BarToFill->GetAnodeIndividualLeft();
      fevt->fNeutronWall.ffastRight[fevt->fNeutronWall.fmulti]=BarToFill->GetAnodeIndividualRight();
      fevt->fNeutronWall.fTimeLeft[fevt->fNeutronWall.fmulti]=BarToFill->GetTimeLeft();
      fevt->fNeutronWall.fTimeRight[fevt->fNeutronWall.fmulti]=BarToFill->GetTimeRight();
      fevt->fNeutronWall.fGeoMean[fevt->fNeutronWall.fmulti]=sqrt(BarToFill->GetAnodeCommonLeft()*BarToFill->GetAnodeCommonRight());
      fevt->fNeutronWall.ffastGeoMean[fevt->fNeutronWall.fmulti]=BarToFill->GetAnodeIndividualLeft()>0 && BarToFill->GetAnodeIndividualRight()>0 ? sqrt(BarToFill->GetAnodeIndividualLeft()*BarToFill->GetAnodeIndividualRight()) : 0;
      fevt->fNeutronWall.fmulti++;
    }
  }

  return;
}
