#include <HTMicroballDetector.h>

//______________________________________________________________________________
HTMicroballDetector::HTMicroballDetector(Int_t detector_number) :
fNumDet(detector_number)
{}

//______________________________________________________________________________
HTMicroballDetector::~HTMicroballDetector()
{}

//______________________________________________________________________________
void HTMicroballDetector::SetTail (Short_t new_value)
{
  fTail=new_value;
}

//______________________________________________________________________________
void HTMicroballDetector::SetE (Short_t new_value)
{
  fE=new_value;
}

//______________________________________________________________________________
void HTMicroballDetector::SetTime (Short_t new_value)
{
  fTime=new_value;
}

//______________________________________________________________________________
Short_t HTMicroballDetector::GetTail () const
{
  return fTail;
}

//______________________________________________________________________________
Short_t HTMicroballDetector::GetE () const
{
  return fE;
}

//______________________________________________________________________________
Short_t HTMicroballDetector::GetTime () const
{
  return fTime;
}

//______________________________________________________________________________
void HTMicroballDetector::Clear ()
{
  fTail=-9999;
  fE=-9999;
  fTime=-9999;
}
