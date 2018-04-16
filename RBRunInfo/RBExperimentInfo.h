#ifndef RBEXPERIMENTINFO_H
#define RBEXPERIMENTINFO_H

/*
* RBExperimentInfo class
* Implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
* v1.0 04/13/2018
*
* The class contains information for each
* configuration file to read run-by-run.
* It can return a RBRunInfo object with the
* information of a specific run.
*
*/


#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

#include <RBRunInfo.h>

class RBExperimentInfo
{
public:
  RBExperimentInfo();                             //! Constructor
  ~RBExperimentInfo();                            //! Destructor

  int InitClass(const char *);                    //! Class Initializer

  int LoadConfiguration(const char *);            //! Read configuration file of the experiment

  RBRunInfo * GetRunInfo(int);                    //! Get RBRunInfo class for a specific run number
  
  void Clear();                                   //!

private:
  std::vector <const char *> fDAQConfigurationFileName;
  std::vector <const char *> fPedestalFileName;
  std::vector <const char *> fMappingFileName;
  
  int fFirstRun;
  int fLastRun;

};

#endif
