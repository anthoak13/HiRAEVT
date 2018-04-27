#ifndef HTNEUTRONWALL_H
#define HTNEUTRONWALL_H

#include <TROOT.h>
#include <TTree.h>
#include <HTNeutronWallRootEvent.h>
#include <HTNeutronWallMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>

class HTNeutronWall : public HTDetector
{
public :
  HTNeutronWall(const char *);                     //!Constructor
  ~HTNeutronWall();                                //!Destructor

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTNeutronWallRootEvent * fevt;                   //!RootEvent type of the detector

};

#endif
