#ifndef HTSISTIMESTAMPE15190_H
#define HTSISTIMESTAMPE15190_H

#include <TROOT.h>
#include <TTree.h>
#include <HTTSe15190RootEvent.h>
#include <HTDetector.h>

class HTSisTimestampe15190 : public HTDetector
{
public :
  HTSisTimestampe15190(const char *);
  ~HTSisTimestampe15190();

  void InitTTreeBranch(TTree *) override;
  void BuildEvent() override;
  void FillMappedData() override;

private :
  HTTSe15190RootEvent * fevt;
  Long64_t fTimestamp;
  Long64_t fTimestampKoreans;

};

#endif
