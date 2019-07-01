#include <HTIonChamberRootEvent.h>

//________________________________________________
HTIonChamberData::HTIonChamberData(int num_detectors) : fmulti(0)
{
  fnumdet  = new Int_t   [num_detectors];
  fE       = new Short_t [num_detectors];
  fTime    = new Double_t[num_detectors];
}

//________________________________________________
HTIonChamberData::~HTIonChamberData()
{
  delete [] fnumdet;
  delete [] fE;
  delete [] fTime;
}

//________________________________________________
HTIonChamberRootEvent::HTIonChamberRootEvent(int num_detectors) :
fNumDetectors(num_detectors),
fIonChamber(fNumDetectors)
{}

//________________________________________________
HTIonChamberRootEvent::~HTIonChamberRootEvent()
{}
