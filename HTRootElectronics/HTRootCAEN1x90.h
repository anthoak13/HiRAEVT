#ifndef HTROOTCAEN1X90_H
#define HTROOTCAEN1X90_H

#include <TROOT.h>
#include <HTRootElectronics.h>

class HTRootCAEN1x90 : public HTRootElectronics
{
public :
  HTRootCAEN1x90(const char *, int);
  ~HTRootCAEN1x90();

  TTreeReaderArray<Double_t> * GetDataPointer() const;  //!Get the pointer to TTreeReaderArray
  double GetData(int) const;                            //!Get the data corresponding to a given channel


private :
  int fNumCh;
  TTreeReaderArray<Double_t> * fData;
};

#endif
