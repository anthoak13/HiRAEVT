#include <HTForwardArrayDetector.h>

//______________________________________________________________________________
HTForwardArrayDetector::HTForwardArrayDetector(int detector_number) : fnumdet(detector_number) {}

//______________________________________________________________________________
HTForwardArrayDetector::~HTForwardArrayDetector() {}

//______________________________________________________________________________
void HTForwardArrayDetector::SetE(Short_t new_value)
{
   fE = new_value;
}

//______________________________________________________________________________
void HTForwardArrayDetector::SetTime(Double_t new_value)
{
   fTime = new_value;
}

//______________________________________________________________________________
Short_t HTForwardArrayDetector::GetE() const
{
   return fE;
}

//______________________________________________________________________________
Double_t HTForwardArrayDetector::GetTime() const
{
   return fTime;
}

//______________________________________________________________________________
void HTForwardArrayDetector::Clear()
{
   fE = -9999;
   fTime = -9999;
}
