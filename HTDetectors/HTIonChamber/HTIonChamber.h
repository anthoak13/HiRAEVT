#ifndef HTIONCHAMBER_H
#define HTIONCHAMBER_H

/* *******************************************************************************************************
 * HTIonChamber Class
 * v1.0 0 7/1/2019
 * class to store ion chamber data
 * implemented by Adam Anthony (anthonya@nscl.msu.edu)
 *
 * - HTIonChamber array
 * | - fDetNum
 * | - fE
 * | - fTime
 */

#include <HTDetector.h>
#include <HTIonChamberMap.h>
#include <HTIonChamberRootEvent.h>
#include <HTRootCAEN1x90.h>
#include <HTRootMADC32.h>
#include <TROOT.h>
#include <TTree.h>

class HTIonChamber : public HTDetector {
public:
   HTIonChamber(const char *, int); //! Constructor
   ~HTIonChamber();                 //! Destructor

   void Clear() override; //! Clear. Not used in the current implementation.

   void InitTTreeBranch(TTree *) override; //! Initialize TTree Branch containing detector ROOT type
   void BuildEvent() override;             //! Calls individual electronic modules to feel detector branches
   void FillMappedData() override; //! Stores mapped data in detector ROOT class to be written on the output tree

private:
   HTIonChamberRootEvent *fevt; //! RootEvent type of the detector

   void InitMapping() override;
};

#endif
