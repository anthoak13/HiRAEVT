#ifndef HTFORWARDARRAYCLUSTER_H
#define HTFORWARDARRAYCLUSTER_H

#include <HTForwardArrayDetector.h>
#include <TROOT.h>

class HTForwardArrayCluster {
private:
   int fNumDetectors;                              // number of detectors in the cluster
   HTForwardArrayDetector **fForwardArrayDetector; // array of Forward Array signle detectors

public:
   HTForwardArrayCluster(int); //!
   ~HTForwardArrayCluster();   //!

   Int_t GetNumberDetectors() const;                 //!
   HTForwardArrayDetector *GetDetector(Int_t) const; //!

   void Clear();
};

#endif
