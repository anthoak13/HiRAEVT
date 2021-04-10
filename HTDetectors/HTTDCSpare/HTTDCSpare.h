#ifndef HTTDCSPARE_H
#define HTTDCSPARE_H

/* *******************************************************************************************************
 * HTTDCSpare Class
 * v1.0 05/22/2018
 * class to store Spare TDC channels usually containing triggers
 * or other useful parameters
 *
 * The class contains a vector of HTTDCSpareChannel objects:
 * - HTTDCSpareChannel
 * |- Double_t fvalue;
 * |- const char * fname;
 */

#include <HTDetector.h>
#include <HTRootCAEN1x90.h>
#include <HTTDCSpareChannel.h>
#include <HTTDCSpareMap.h>
#include <TROOT.h>
#include <TTree.h>

class HTTDCSpare : public HTDetector {
public:
   HTTDCSpare(const char *); //! Constructor
   ~HTTDCSpare();            //! Destructor

   void Clear() override; //! Clear. Not used in the current implementation.

   void InitTTreeBranch(TTree *) override; //! Initialize TTree Branch containing detector ROOT type
   void BuildEvent() override;             //! Calls individual electronic modules to fill detector branches
   void FillMappedData() override; //! Stores mapped data in detector ROOT class to be written on the output tree

private:
   std::vector<HTTDCSpareChannel *> fSpareChannels; //! HTTDCSpareChannel array containing event-by-event mapped data

   void InitMapping() override;
};

#endif
