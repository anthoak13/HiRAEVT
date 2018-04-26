#include <HTRootCAEN7xx.h>

//________________________________________________
HTRootCAEN7xx::HTRootCAEN7xx(const char * name) : HTRootElectronics(name),
fNumCh(32),
fData(0)
{}

//________________________________________________
HTRootCAEN7xx::~HTRootCAEN7xx()
{
  if(fData) delete [] fData;
}

//________________________________________________
Short_t HTRootCAEN7xx::GetData(int ch) const
{
  return (*fData)[ch];
}

//________________________________________________
TTreeReaderArray<Short_t> * HTRootCAEN7xx::GetDataPointer() const
{
  return fData;
}
