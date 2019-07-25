#ifndef HTMICROBALL_H
#define HTMICROBALL_H

#include <TROOT.h>
#include <TTree.h>
#include <HTMicroballRootEvent.h>
#include <HTMicroballMap.h>
#include <HTRootCAEN7xx.h>
#include <HTDetector.h>
#include <HTShared.h>

#include <HTMicroballArray.h>

class HTMicroball : public HTDetector
{
public :
  HTMicroball(const char *);                       //!Constructor
  ~HTMicroball();                                  //!Destructor

  void Clear() override;                           //!Clear to -9999

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTMicroballArray *fMicroball;                    //!HTMicroballRing object containing event-by-event mapped data
  HTMicroballRootEvent * fevt;                     //!RootEvent type of the detector
  int fNumDetectors;                               //!Number of detectors

  void InitMapping() override;
};

#endif
