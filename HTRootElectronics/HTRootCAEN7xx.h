#ifndef HTROOTCAEN7XX_H
#define HTROOTCAEN7XX_H

#include <TROOT.h>
#include <HTRootElectronics.h>

class HTRootCAEN7xx : public HTRootElectronics
{
public :
  HTRootCAEN7xx(const char *);
  ~HTRootCAEN7xx();

  TTreeReaderArray<Short_t> * GetDataPointer() const;  //!Get the pointer to TTreeReaderArray
  Short_t GetData(int) const;                          //!Get the data corresponding to a given channel

private :
  int fNumCh;
  TTreeReaderArray<Short_t> * fData;

};

#endif
