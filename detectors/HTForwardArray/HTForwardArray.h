#ifndef HTFORWARDARRAY_H
#define HTFORWARDARRAY_H

#include <TROOT.h>
#include <TTree.h>
#include <HTForwardArrayRootEvent.h>
#include <HTForwardArrayMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>

class HTForwardArray : public HTDetector
{
public :
  HTForwardArray(const char *);                    //!Constructor
  ~HTForwardArray();                               //!Destructor

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTForwardArrayRootEvent * fevt;                  //!RootEvent type of the detector

};

#endif
