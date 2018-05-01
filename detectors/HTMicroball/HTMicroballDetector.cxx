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
void HTMicroballDetector::SetFast (Short_t new_value)
{
  fFast=new_value;
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
Short_t HTMicroballDetector::GetFast () const
{
  return fFast;
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
  fFast=-9999;
  fTime=-9999;
}
