#include <HTTDCSpareChannel.h>

//________________________________________________
HTTDCSpareChannel::HTTDCSpareChannel(const char * name) :
fname(name),
fvalue(-9999)
{}

//________________________________________________
HTTDCSpareChannel::~HTTDCSpareChannel()
{}

//________________________________________________
Double_t HTTDCSpareChannel::GetValue() const
{
  return fvalue;
}

//________________________________________________
const Double_t * HTTDCSpareChannel::GetValuePointer() const
{
  return &fvalue;
}

//________________________________________________
const char * HTTDCSpareChannel::GetName() const
{
  return fname.c_str();
}

//________________________________________________
void HTTDCSpareChannel::SetValue(Double_t new_value)
{
  fvalue=new_value;
}
