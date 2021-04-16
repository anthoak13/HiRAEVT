#ifndef HTUNPACKER_H
#define HTUNPACKER_H

// This class is responsible for unpacking data from NSCL streams. It supports both merged
// and unmerged data. It contains an instance of HTExperiment, that it writes to a tree,
// and HTExperimentInfo, which it writes to the file the TTree is in, describing the electronics
// information. HTExperimentInfo contains the complete information needed for the
// Mapper to properly read the TTree.

#include "Rtypes.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CPhysicsEventItem;
class CRingStateChangeItem;
class CRingItem;
class HTExperiment;
class HTExperimentInfo;
class HTModuleUnpacker;
class TFile;
class TTree;


class HTUnpacker {

private:
   Bool_t kMergedData;

   HTExperiment *fExperiment; //Unpacked data
   HTExperimentInfo *fExperimentInfo; //metadata for run
   TTree *fOutTree;
   TFile *fOutFile;

   
   std::map<Int_t, std::vector<HTModuleUnpacker *>> stackMap; //key:stackID value:moduleList
   ULong_t fEventUnpacked;
   std::map<Int_t, ULong_t> fBufferMismatchCount;


   
   void CreateUnpackers(json moduleList);
   void UnpackStack(UShort_t *pEvent, UInt_t offset);

   static ULong_t getLong(std::vector<UShort_t> &event, ULong_t offset);

public:
   HTUnpacker(json configJson, Int_t runNum);
   ~HTUnpacker();

   CRingItem *handleStateChangeItem(CRingStateChangeItem *pItem);
   CRingItem *handlePhysicsEventItem(CPhysicsEventItem *pItem);

   void PrintSummary();

   HTExperiment *GetExperiment() { return fExperiment; }
   HTExperimentInfo *GetExperimentInfo() { return fExperimentInfo; }
   std::vector<HTModuleUnpacker *> &GetStackModuleList(Int_t stackID) { return stackMap.at(stackID); }
};

#endif // #ifndef HTUNPACKER_H
