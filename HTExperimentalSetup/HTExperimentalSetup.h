#ifndef HTEXPERIMENTALSETUP_H
#define HTEXPERIMENTALSETUP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <HTRootElectronics.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTRootHINP.h>
#include <HTRootSisTimestamp.h>
#include <HTRootTimestamp.h>
#include <HTDetector.h>
#include <HTSisTimestampe15190.h>
#include <HTDetectorMap.h>
#include <HTSisTimestampe15190Map.h>
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

  int ParseDefineMappingLine(const char *);          //!Parse a define line in .map file. Returns 1 if a detector is add, otherwise 0.
  int ParseAssignMappingLine(const char *);          //!Parse a assign line in .map file. Returns the number of module assigned.

  std::map<std::string, HTRootElectronics *> * GetModules() const; //!Get a std::map<std::string, HTRootElectronics *> pointer to the defined modules
  HTRootElectronics * GetModule(std::string) const;                //!Get a module by name.
  HTRootElectronics * GetModule(const char *) const;               //!Get a module by name.
  HTDetector * GetDetector(std::string) const;                    //!Get a detector by name
  HTDetector * GetDetector(const char *) const;                    //!Get a detector by name
  int GetNDetectors() const;                                       //!Get the number of defined detectors

private :
  std::map<std::string, HTRootElectronics *> *fModules;
  std::map<std::string, HTDetector *> *fDetectors;
  std::map<std::string, HTDetectorMap *> *fDetectorMaps;

};

#endif
