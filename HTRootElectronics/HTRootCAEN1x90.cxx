#include <HTRootCAEN1x90.h>

//________________________________________________
HTRootCAEN1x90::HTRootCAEN1x90(const char * name, int numch) : HTRootElectronics(name),
fNumCh(numch),
fData(0)
{}

//________________________________________________
HTRootCAEN1x90::~HTRootCAEN1x90()
{
  if(fData) delete [] fData;
}

//________________________________________________
double HTRootCAEN1x90::GetData(int ch) const
{
  return (*fData)[ch];
}

//________________________________________________
TTreeReaderArray<Double_t> * HTRootCAEN1x90::GetDataPointer() const
{
  return fData;
}
