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
#include <iomanip>
#include <stdio.h>

#include <RBRunInfo.h>

class RBExperimentInfo
{
public:
  RBExperimentInfo();                             //! Constructor
  ~RBExperimentInfo();                            //! Destructor

  int InitClass(const char *);                    //! Class Initializer

  int LoadSetupConfiguration(const char *);       //! Read general setup lines from configuration file of the experiment
  int LoadRunConfiguration(const char *, int);    //! Read run configuration for a specific run

  RBRunInfo * GetRunInfo(int) const;              //! Get RBRunInfo class for a specific run number
  bool IsDataMerged() const;                      //!
  const char * GetName() const;                   //!
  const char * GetTitle() const;                  //!
  const char * GetEvtFilePath() const;            //!
  const char * GetRootFilePath() const;           //!

  void Clear();                                   //!

private:
  std::string * fDAQConfigurationFileName;
  std::string * fPedestalFileName;
  std::string * fMappingFileName;
  std::string * fRunEvtFilePath;
  std::string * fRunTitle;

  bool fDataMerged;
  std::string fExperimentName;
  std::string fExperimentTitle;
  std::string fEvtFilePath;
  std::string fRootFilePath;

  int fFirstRun;
  int fLastRun;

  void ParseSetConfigLine(const char *);              //! Parse a configuration line containing the command "set" and extract Experiment info
  void ParseSetConfigLineRunInfo(const char *, int);  //! Parse a configuration line containing the command "set" and extract Run info
  const char * RetrieveRunTitleFromEvtFile(const char *) const;     //! Returns run title taken from the evt file given as input
};

#endif
