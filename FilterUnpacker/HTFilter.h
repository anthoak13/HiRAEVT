#ifndef CUNPACKERFILTER_CPP
#define CUNPACKERFILTER_CPP

// CUnpackerfilter
// Adam Anthony 4/14/2021
// This class is responsible for unpacking data from NSCL streams. It supports both merged
// and unmerged data. It contains an instance of HTExperiment, that it writes to a tree, and HTExperimentInfo, which it writes to the file the TTree is in, describing the electronics information. HTExperimentInfo contains the complete information needed for the Mapper to properly read the TTree. 


#include <CFilter.h>
#include <stdint.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CPhysicsEventItem;
class HTExperiment;
class HTExperimentInfo;

class HTFilter : public CFilter {

private:
   HTExperiment *fExperiment;
   HTExperimentInfo *fExperimentInfo;
   
public:
   HTFilter(json configJson);
   //HTFilter(HTFilter const &other);
   ~HTFilter();

   
   virtual HTFilter *clone() const override { return new HTFilter(*this); }

   virtual CRingItem *handleStateChangeItem(CRingStateChangeItem *pItem) override;
   virtual CRingItem *handlePhysicsEventItem(CPhysicsEventItem *pItem) override;

   HTExperiment *GetExperiment() {  return fExperiment; }
   HTExperimentInfo *GetExperimentInfo() {  return fExperimentInfo; }
};

#endif
