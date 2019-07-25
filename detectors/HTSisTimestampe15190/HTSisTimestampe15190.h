#ifndef HTSISTIMESTAMPE15190_H
#define HTSISTIMESTAMPE15190_H

#include <TROOT.h>
#include <TTree.h>
#include <HTTSe15190RootEvent.h>
#include <HTSisTimestampe15190Map.h>
#include <HTRootTimestamp.h>
#include <HTRootSisTimestamp.h>
#include <HTDetector.h>

class HTSisTimestampe15190 : public HTDetector
{
public :
  HTSisTimestampe15190(const char *);              //!Constructor
  ~HTSisTimestampe15190();                         //!Destructor

  void Clear() override;                           //!Clear (not used in the current implementation)

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTTSe15190RootEvent * fevt;                      //!RootEvent type of the detector
  Long64_t fTimestamp;
  Long64_t fTimestampKoreans;

  void InitMapping() override;
};

#endif
