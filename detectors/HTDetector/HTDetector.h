#ifndef HTDETECTOR_H
#define HTDETECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <TTree.h>

#include "HTRootElectronics.h"
#include "HTDetectorMap.h"

class HTDetector
{
public :
  HTDetector(const char *, int num_detectors = 0);  //!Constructor
  virtual ~HTDetector();                          //!Destructor

  virtual void Clear();                           //!Clear detector data to -9999

  void AssignModule(HTRootElectronics *);         //!Assign a module to the detector

  const char * GetName() const;                   //!Returns detector name
  const char * GetType() const;                   //!Returns detector type
  int GetNumDetectors() const;                    //!Get number of individual detection objects (telescopes, bars, sectors, ...)

  void LoadMapping(const char *);

  virtual void InitTTreeBranch(TTree *);          //!Individually implemented in specific detector classes
  virtual void BuildEvent();                      //!Individually implemented in specific detector classes
  virtual void FillMappedData();                  //!Individually implemented in specific detector classes
  virtual void InitMapping() = 0;                 //!Create a detector mapping of the right type
  
protected :


  std::string fName;                              //!Detector Name
  std::string fType;                              //!Detector Type
  int fNumDetectors;                              //!Number of individual detection objects (telescopes, bars, sectors, ...)
  std::vector<HTRootElectronics *> fModules;      //!HTRootElectronics modules
  HTDetectorMap * fDetectorMapping;               //!Detector Mapping

  
};

#endif
