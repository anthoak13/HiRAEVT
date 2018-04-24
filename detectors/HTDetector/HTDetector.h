#ifndef HTDETECTOR_H
#define HTDETECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <TTree.h>
#include <HTRootElectronics.h>
#include <HTDetectorMap.h>

class HTDetector
{
public :
  HTDetector();                                   //!Constructor
  ~HTDetector();                                  //!Destructor

  void AssignModule(HTRootElectronics *);         //!Assign a module to the detector
  void SetMapping(HTDetectorMap *);               //!SetDetector Mapping

  virtual void InitTTreeBranch(TTree *);          //!Individualli implemented in specific detector class
  virtual void BuildEvent();                      //!Individualli implemented in specific detector class

private :
  std::vector<HTRootElectronics *> fModules;           //!HTRootElectronics modules
  HTDetectorMap * fDetectorMapping;               //!Detector Mapping
};

#endif
