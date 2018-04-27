#ifndef HTMICROBALL_H
#define HTMICROBALL_H

#include <TROOT.h>
#include <TTree.h>
#include <HTMicroballRootEvent.h>
#include <HTMicroballMap.h>
#include <HTRootCAEN7xx.h>
#include <HTDetector.h>

class HTMicroball : public HTDetector
{
public :
  HTMicroball(const char *);                       //!Constructor
  ~HTMicroball();                                  //!Destructor

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTMicroballRootEvent * fevt;                     //!RootEvent type of the detector

};

#endif
