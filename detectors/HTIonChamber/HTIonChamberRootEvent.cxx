#include <HTIonChamberRootEvent.h>

//________________________________________________
HTIonChamberData::HTIonChamberData(int num_detectors) : fMulti(0)
{
  fDetNum  = new Int_t   [num_detectors];
  fE       = new Short_t [num_detectors];
  fTime    = new Double_t[num_detectors];
}

//________________________________________________
HTIonChamberData::~HTIonChamberData()
{
  delete [] fDetNum;
  delete [] fE;
  delete [] fTime;
}

//________________________________________________
HTIonChamberRootEvent::HTIonChamberRootEvent(int num_detectors) :
fIonChamber(num_detectors)
{}

//________________________________________________
HTIonChamberRootEvent::~HTIonChamberRootEvent()
{}
