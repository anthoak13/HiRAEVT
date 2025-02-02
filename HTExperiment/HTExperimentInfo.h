#ifndef HTEXPERIMENTINFO_H
#define HTEXPERIMENTINFO_H

// This class hold information on the current run and experimental setup
#include "TDatime.h"
#include "TObject.h"
#include "TString.h"

#include "Rtypes.h"

class HTExperimentInfo : public TObject {

private:
   TString fRunTitle;
   Int_t fRunNumber;
   TDatime fStartTime;
   TDatime fEndTime;
   Int_t fExperimentNumber;
   TString fName;

public:
   HTExperimentInfo(Int_t experimentNumber = -1);
   void SetRunTitle(TString title) { fRunTitle = title; }
   void SetRunNumber(Int_t runNumber) { fRunNumber = runNumber; }
   void SetStartTime(TDatime time) { fStartTime = time; }
   void SetEndTime(TDatime time) { fEndTime = time; }

   TString GetRunTitle() { return fRunTitle; }
   Int_t GetRunNumber() { return fRunNumber; }
   TDatime GetStartTime() { return fStartTime; }
   TDatime GetEndTime() { return fEndTime; }

   virtual const char *GetName() const override { return fName.Data(); }
   ClassDefOverride(HTExperimentInfo, 1);
};

#endif //#ifndef HTEXPERIMENTINFO_H
