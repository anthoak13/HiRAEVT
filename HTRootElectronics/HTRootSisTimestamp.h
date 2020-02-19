#ifndef HTROOTSISTIMESTAMP_H
#define HTROOTSISTIMESTAMP_H

#include <TROOT.h>
#include <HTRootElectronics.h>
#include <TTreeReaderValue.h>

class HTRootSisTimestamp : public HTRootElectronics
{
public :
  HTRootSisTimestamp(const char *);                             //!Constructor
  ~HTRootSisTimestamp();                                        //!Destructor

  void InitTreeInputBranch(TTreeReader&) override;              //!Set Input TTRee Reader Branch
  ULong64_t GetData(int ch) const;                                     //!Get Timestamp

private :
  TTreeReaderArray<ULong64_t> *fTimestamp;
};

#endif
