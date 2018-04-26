#ifndef HTEXPERIMENTALSETUP_H
#define HTEXPERIMENTALSETUP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <HTRootElectronics.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTRootHINP.h>
#include <HTRootSisTimestamp.h>
#include <HTRootTimestamp.h>
#include <HTDetector.h>
#include <HTDetectorMap.h>
#include <HTRunInfo.h>
#include <HTExperimentInfo.h>
#include <HTDAQStackInfo.h>
#include <HTModuleInfo.h>
#include <HTShared.h>

class HTExperimentalSetup
{
public :
  HTExperimentalSetup();                             //!Constructor
  ~HTExperimentalSetup();                            //!Destructor

  int BuildElectronicModules();                      //!Called by HTMapper::BuildExperimentalSetup()
  int BuildDetectors();                              //!Called by HTMapper::BuildExperimentalSetup()
  int BuildDetectorMaps();                           //!Called by HTMapper::BuildExperimentalSetup()

  std::map<int, HTRootElectronics *> * GetModules() const; //!Get a std::map<int, HTRootElectronics *> pointer to the defined modules
  HTRootElectronics * GetModule(int) const;                //!Get a module by index. Index is defined as STACK*100+VSN
  HTRootElectronics * GetModule(const char *) const;       //!Get a module by name.
  HTDetector * GetDetector(int) const;                     //!Get a detector by index
  int GetNDetectors() const;                               //!Get the number of defined detectors

private :
  std::map<int, HTRootElectronics *> *fModules;
  std::map<std::string, HTRootElectronics *> *fModulesNamesMapped;
  std::vector<HTDetector *> fDetectors;
  std::vector<HTDetectorMap *> fDetectorMaps;

};

#endif
