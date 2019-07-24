#ifndef HTROOTMADC32_H
#define HTROOTMADC32_H

#include <TROOT.h>
#include <HTRootElectronics.h>
#include <sstream>

class HTRootMADC32 : public HTRootElectronics
{
public :
  HTRootMADC32(const char *);
  ~HTRootMADC32();

  TTreeReaderArray<Short_t> * GetDataPointer() const;  //!Get the pointer to TTreeReaderArray
  Short_t GetData(int) const;                          //!Get the data corresponding to a given channel
  void InitTreeInputBranch(TTreeReader&) override;     //!Set Input TTreeReader Branch

private :
  int fNumCh;
  TTreeReaderArray<Short_t> * fData;
  Short_t fOverflow;

};

#endif
