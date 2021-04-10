#include <HTForwardArrayRootEvent.h>

//________________________________________________
HTForwardArrayData::HTForwardArrayData(int num_detectors) : fmulti(0)
{
   fnumdet = new Int_t[num_detectors];
   fE = new Short_t[num_detectors];
   fTime = new Double_t[num_detectors];
}

//________________________________________________
HTForwardArrayData::~HTForwardArrayData()
{
   delete[] fnumdet;
   delete[] fE;
   delete[] fTime;
}

//________________________________________________
HTForwardArrayRootEvent::HTForwardArrayRootEvent(int num_detectors)
   : fNumDetectors(num_detectors), fForwardArray(fNumDetectors)
{
}

//________________________________________________
HTForwardArrayRootEvent::~HTForwardArrayRootEvent() {}
