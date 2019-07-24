#include <HTRootMADC32.h>

//________________________________________________
HTRootMADC32::HTRootMADC32(const char * name) : HTRootElectronics(name),
fNumCh(32),
fData(0),
fOverflow(8192)
{
}

//________________________________________________
HTRootMADC32::~HTRootMADC32()
{
  if(fData) delete [] fData;
}

//________________________________________________
Short_t HTRootMADC32::GetData(int ch) const
{
  double datum=(*fData)[ch];

  return datum>=0 ? datum : -9999;
}

//________________________________________________
TTreeReaderArray<Short_t> * HTRootMADC32::GetDataPointer() const
{
  return fData;
}

void HTRootMADC32::InitTreeInputBranch(TTreeReader& theReader)
{
  fData = new TTreeReaderArray<Short_t>(theReader, GetName());
}
