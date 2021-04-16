#ifndef CUNPACKERFILTER_CPP
#define CUNPACKERFILTER_CPP

// CUnpackerfilter
// Adam Anthony 4/14/2021
// This class is responsible for unpacking data from NSCL streams. It supports both merged
// and unmerged data. It contains an instance of HTExperiment, that it writes to a tree, and HTExperimentInfo, which it
// writes to the file the TTree is in, describing the electronics information. HTExperimentInfo contains the complete
// information needed for the Mapper to properly read the TTree.

#include "TString.h"

#include <CFilter.h>
#include <stdint.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CPhysicsEventItem;
class HTExperiment;
class HTExperimentInfo;
class HTModuleUnpacker;

class HTFilter : public CFilter {

private:
   Bool_t kMergedData;

   HTExperiment *fExperiment;
   HTExperimentInfo *fExperimentInfo;

   // Key is stack ID, the vector is a list of the modules
   std::map<Int_t, std::vector<HTModuleUnpacker *>> stackMap;

   ULong_t *fEventUnpacked; // This is a pointer because of the stupid NSCLDAQ cloning
   std::map<Int_t, ULong_t> fBufferMismatchCount;

   void CreateUnpackers(json moduleList);
   void UnpackStack(UShort_t *pEvent, UInt_t offset);
   static ULong_t getLong(std::vector<UShort_t> &event, ULong_t offset);

   // TString GetStringFromJSON(json data);

public:
   HTFilter(json configJson);
   ~HTFilter();

   virtual HTFilter *clone() const override { return new HTFilter(*this); }

   virtual CRingItem *handleStateChangeItem(CRingStateChangeItem *pItem) override;
   virtual CRingItem *handlePhysicsEventItem(CPhysicsEventItem *pItem) override;

   void PrintSummary();

   HTExperiment *GetExperiment() { return fExperiment; }
   HTExperimentInfo *GetExperimentInfo() { return fExperimentInfo; }
   std::vector<HTModuleUnpacker *> &GetStackModuleList(Int_t stackID) { return stackMap.at(stackID); }
};

#endif
