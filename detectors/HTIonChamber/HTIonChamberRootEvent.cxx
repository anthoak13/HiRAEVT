#include <HTIonChamberRootEvent.h>

//________________________________________________
HTIonChamberData::HTIonChamberData(int numDetectors) : fMulti(0)
{
  if(numDetectors > MAXNUMDET)
    throw std::invalid_argument(TString::Format(
				  "Tried to create %d detectors which is larger then the absolute cap of %d",
				  numDetectors, MAXNUMDET).Data());

  fDetNum  = new Int_t   [numDetectors];
  fE       = new Short_t [numDetectors];
  fTime    = new Double_t[numDetectors];
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
