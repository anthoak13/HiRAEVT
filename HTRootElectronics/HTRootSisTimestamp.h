#ifndef HTROOTSISTIMESTAMP_H
#define HTROOTSISTIMESTAMP_H

#include <TROOT.h>
#include <HTRootElectronics.h>
#include <TTreeReaderValue.h>

class HTRootSisTimestamp : public HTRootElectronics
{
public :
  HTRootSisTimestamp(const char *);
  ~HTRootSisTimestamp();

  void InitTreeInputBranch(TTreeReader&) override;
  Long64_t GetData() const;
  Long64_t GetDataKoreans() const;

private :
  TTreeReaderValue<Long64_t> * fTimestamp;
  TTreeReaderValue<Long64_t> * fTimestampKoreans;
};

#endif
