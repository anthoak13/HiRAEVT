#ifndef HTVETOWALL_H
#define HTVETOWALL_H

#include <TROOT.h>
#include <TTree.h>
#include <HTVetoWallRootEvent.h>
#include <HTVetoWallMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>

class HTVetoWall : public HTDetector
{
public :
  HTVetoWall(const char *);                        //!Constructor
  ~HTVetoWall();                                   //!Destructor

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTVetoWallRootEvent * fevt;                      //!RootEvent type of the detector

};

#endif
