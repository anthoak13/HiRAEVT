#include <HTVetoWall.h>

#define dModuleBottom(bar) ((HTVetoWallMap *)fDetectorMapping)->GetBottomModule(bar)
#define dChannelBottom(bar) ((HTVetoWallMap *)fDetectorMapping)->GetBottomChannel(bar)
#define dModuleTop(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTopModule(bar)
#define dChannelTop(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTopChannel(bar)
#define dModuleTimeBottom(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTimeBottomModule(bar)
#define dChannelTimeBottom(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTimeBottomChannel(bar)
#define dModuleTimeTop(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTimeTopModule(bar)
#define dChannelTimeTop(bar) ((HTVetoWallMap *)fDetectorMapping)->GetTimeTopChannel(bar)

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
  theTree->Branch(Form("%s.",fName.c_str()),
		  "HTVetoWallData",
		  &(fevt->fVetoWall),
		  32768,2);
  return;
}

//________________________________________________
void HTVetoWall::BuildEvent()
{
  //Retrieving information from HTRootModule types
  for(int NumBar=0; NumBar<fNumDetectors; NumBar++) {
    fVetoWall->GetBar(NumBar)->SetAnodeCommonBottom(dModuleBottom(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleBottom(NumBar)])->GetData(dChannelBottom(NumBar)) : -9999);
    fVetoWall->GetBar(NumBar)->SetAnodeCommonTop(dModuleTop(NumBar)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleTop(NumBar)])->GetData(dChannelTop(NumBar)) : -9999);
    fVetoWall->GetBar(NumBar)->SetTimeBottom(dModuleTimeBottom(NumBar)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTimeBottom(NumBar)])->GetData(dChannelTimeBottom(NumBar)) : -9999);
    fVetoWall->GetBar(NumBar)->SetTimeTop(dModuleTimeTop(NumBar)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTimeTop(NumBar)])->GetData(dChannelTimeTop(NumBar)) : -9999);
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTVetoWall::FillMappedData()
{
  //Retrieving information from HTVetoWallArray to fill HTVetoWallData object
  fevt->fVetoWall.fmulti=0;
  for(int NumBar=0; NumBar<fNumDetectors; NumBar++) {
    HTVetoWallBar * BarToFill = fVetoWall->GetBar(NumBar);
    if(BarToFill->GetAnodeCommonBottom()>0 && BarToFill->GetAnodeCommonTop()>0 && BarToFill->GetTimeBottom()!=-9999 && BarToFill->GetTimeTop()!=-9999)
    {
      fevt->fVetoWall.fnumbar[fevt->fVetoWall.fmulti]=NumBar;
      fevt->fVetoWall.fBottom[fevt->fVetoWall.fmulti]=BarToFill->GetAnodeCommonBottom();
      fevt->fVetoWall.fTop[fevt->fVetoWall.fmulti]=BarToFill->GetAnodeCommonTop();
      fevt->fVetoWall.fTimeBottom[fevt->fVetoWall.fmulti]=BarToFill->GetTimeBottom();
      fevt->fVetoWall.fTimeTop[fevt->fVetoWall.fmulti]=BarToFill->GetTimeTop();
      fevt->fVetoWall.fGeoMean[fevt->fVetoWall.fmulti]=sqrt(BarToFill->GetAnodeCommonBottom()*BarToFill->GetAnodeCommonTop());
      fevt->fVetoWall.fmulti++;
    }
  }
  return;
}

void HTVetoWall::InitMapping()
{
  fDetectorMapping = new HTVetoWallMap(fName, fNumDetectors);
}
