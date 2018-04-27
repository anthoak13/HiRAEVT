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
  Long64_t GetData() const;                                     //!Get Timestamp
  Long64_t GetDataKoreans() const;                              //!Get Timestamp for Korean electronics

private :
  TTreeReaderValue<Long64_t> * fTimestamp;
  TTreeReaderValue<Long64_t> * fTimestampKoreans;
};

#endif
