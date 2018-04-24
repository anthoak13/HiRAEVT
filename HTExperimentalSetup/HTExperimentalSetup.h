#ifndef HTEXPERIMENTALSETUP_H
#define HTEXPERIMENTALSETUP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <HTRootElectronics.h>
#include <HTDetector.h>
#include <HTDetectorMap.h>

class HTExperimentalSetup
{
public :
  HTExperimentalSetup();                             //!Constructor
  ~HTExperimentalSetup();                            //!Destructor

  int BuildElectronicModules();                      //!Called by HTMapper::BuildExperimentalSetup()
  int BuildDetectors();                              //!Called by HTMapper::BuildExperimentalSetup()
  int BuildDetectorMaps();                           //!Called by HTMapper::BuildExperimentalSetup()

  HTRootElectronics * GetModule(const char *) const; //!Get a module by name
  HTRootElectronics * GetModule(int) const;          //!Get a module by index
  HTDetector * GetDetector(int) const;               //!Get a detector by index
  int GetNDetectors() const;                         //!Get the number of defined detectors

private :
  std::vector<HTRootElectronics *> fModules;
  std::vector<HTDetector *> fDetectors;
  std::vector<HTDetectorMap *> fDetectorMaps;

};

#endif
