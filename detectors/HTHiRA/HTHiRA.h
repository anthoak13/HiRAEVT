#ifndef HTHIRA_H
#define HTHIRA_H

#include <TROOT.h>
#include <TTree.h>
#include <HTHiRARootEvent.h>
#include <HTHiRAMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTRootHINP.h>
#include <HTDetector.h>

class HTHiRA : public HTDetector
{
public :
  HTHiRA(const char *, int);                        //!Constructor
  ~HTHiRA();                                        //!Destructor

  void Clear() override;                           //!Clear to -9999  

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTHiRARootEvent * fevt;                          //!RootEvent type of the detector

};

#endif
