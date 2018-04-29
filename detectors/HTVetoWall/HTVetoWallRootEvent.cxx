#include <HTVetoWallRootEvent.h>

//________________________________________________
HTVetoWallData::HTVetoWallData(int num_bars) : fmulti(0)
{
  fnumbar    =new Int_t   [num_bars];
  fTop       =new Short_t [num_bars];
  fBottom    =new Short_t [num_bars];
  fTimeTop   =new Double_t[num_bars];
  fTimeBottom=new Double_t[num_bars];
  fGeoMean   =new Double_t[num_bars];
}

//________________________________________________
HTVetoWallData::~HTVetoWallData()
{}

//________________________________________________
HTVetoWallRootEvent::HTVetoWallRootEvent(int num_bars) :
fNumBars(num_bars),
fVetoWall(fNumBars)
{}

//________________________________________________
HTVetoWallRootEvent::~HTVetoWallRootEvent()
{}
