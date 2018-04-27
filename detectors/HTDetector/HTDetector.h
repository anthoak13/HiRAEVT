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
  virtual ~HTDetector();                          //!Destructor

  void AssignModule(HTRootElectronics *);         //!Assign a module to the detector
  void SetMapping(HTDetectorMap *);               //!SetDetector Mapping

  const char * GetName() const;                   //!Returns detector name
  const char * GetType() const;                   //!Returns detector type

  virtual void InitTTreeBranch(TTree *);          //!Individually implemented in specific detector classes
  virtual void BuildEvent();                      //!Individually implemented in specific detector classes
  virtual void FillMappedData();                  //!Individually implemented in specific detector classes

protected :
  std::string fName;                              //!Detector Name
  std::string fType;                              //!Detector Type
  std::vector<HTRootElectronics *> fModules;      //!HTRootElectronics modules
  HTDetectorMap * fDetectorMapping;               //!Detector Mapping
};

#endif
