#include <HTMicroballRootEvent.h>

//________________________________________________
HTMicroballData::HTMicroballData(int num_detectors)
{
  fnumring =new Int_t   [num_detectors];
  fnumdet  =new Int_t   [num_detectors];
  fTail    =new Short_t [num_detectors];
  fE       =new Short_t [num_detectors];
  fTime    =new Short_t [num_detectors];
}

//________________________________________________
HTMicroballData::~HTMicroballData()
{
  delete [] fnumring;
  delete [] fnumdet ;
  delete [] fTail   ;
  delete [] fE      ;
  delete [] fTime   ;
}

//________________________________________________
HTMicroballRootEvent::HTMicroballRootEvent(int num_detectors) :
fNumDetectors(num_detectors),
fMicroball(fNumDetectors)
{}

//________________________________________________
HTMicroballRootEvent::~HTMicroballRootEvent()
{}
