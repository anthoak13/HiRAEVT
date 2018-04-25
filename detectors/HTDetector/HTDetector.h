#ifndef HTDETECTOR_H
#define HTDETECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <TTree.h>
#include <HTRootElectronics.h>
#include <HTDetectorMap.h>

class HTDetector
{
public :
  HTDetector(const char *);                       //!Constructor
  ~HTDetector();                                  //!Destructor

  void AssignModule(HTRootElectronics *);         //!Assign a module to the detector
  void SetMapping(HTDetectorMap *);               //!SetDetector Mapping

  const char * GetName() const;                   //!Returns detector name

  virtual void InitTTreeBranch(TTree *);          //!Individually implemented in specific detector class
  virtual void BuildEvent();                      //!Individually implemented in specific detector class

private :
  const char * fName;                             //!Detector Name
  std::vector<HTRootElectronics *> fModules;      //!HTRootElectronics modules
  HTDetectorMap * fDetectorMapping;               //!Detector Mapping
};

#endif
