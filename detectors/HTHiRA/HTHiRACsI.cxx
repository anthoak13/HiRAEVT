#include <HTHiRACsI.h>

//________________________________________________
HTHiRACsI::HTHiRACsI() :
fEnergy(-9999),
fTime(-9999)
{}

//________________________________________________
HTHiRACsI::~HTHiRACsI()
{}

//________________________________________________
void HTHiRACsI::Clear()
{
  fEnergy=-9999;
  fTime=-9999;
}

//________________________________________________
Short_t HTHiRACsI::GetEnergy() const
{
  return fEnergy;
}

//________________________________________________
Double_t HTHiRACsI::GetTime() const
{
  return fTime;
}

//________________________________________________
void HTHiRACsI::SetEnergy(Short_t newEnergy)
{
  fEnergy=newEnergy;
}

//________________________________________________
void HTHiRACsI::SetTime(Double_t newTime)
{
  fTime=newTime;
}
