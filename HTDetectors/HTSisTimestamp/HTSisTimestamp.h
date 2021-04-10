#ifndef HTSISTIMESTAMP_H
#define HTSISTIMESTAMP_H

/* *******************************************************************************************************
 * HTSisTimestamp Class
 * v1.0 0 2/18/2020
 * class to store timestamp data
 * implemented by Adam Anthony (anthonya@nscl.msu.edu)
 * modified from Daniele
 *
 * - HTSisTimestamp array
 * | - fTimestamp
 */

#include <HTDetector.h>
#include <HTRootSisTimestamp.h>
#include <HTRootTimestamp.h>
#include <HTSisTimestampMap.h>
#include <HTSisTimestampRootEvent.h>
#include <TROOT.h>
#include <TTree.h>

class HTSisTimestamp : public HTDetector {
public:
   HTSisTimestamp(const char *, int numDetg); //! Constructor
   ~HTSisTimestamp();                         //! Destructor

   void Clear() override; //! Clear (not used in the current implementation)

   void InitTTreeBranch(TTree *) override; //! Initialize TTree Branch containing detector ROOT type
   void BuildEvent() override;             //! Calls individual electronic modules to feel detector branches
   void FillMappedData() override; //! Stores mapped data in detector ROOT class to be written on the output tree

private:
   HTSisTimestampRootEvent *fevt; //! RootEvent type of the detector

   void InitMapping() override;
};

#endif
