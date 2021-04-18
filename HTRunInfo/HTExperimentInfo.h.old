#ifndef HTEXPERIMENTINFO_H
#define HTEXPERIMENTINFO_H

/*
 * HTExperimentInfo class
 * Implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * v1.0 04/13/2018
 *
 * The class contains information for each
 * configuration file to read run-by-run.
 * It can return a HTRunInfo object with the
 * information of a specific run.
 *
 */

#include <HTRunInfo.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

class HTExperimentInfo {

public:
   static HTExperimentInfo *Instance();

   int InitClass(const char *); //! Class Initializer

   int LoadSetupConfiguration(const char *);    //! Read general setup lines from configuration file of the experiment
   int LoadRunConfiguration(const char *, int); //! Read run configuration for a specific run

   HTRunInfo *GetRunInfo() const; //! Get HTRunInfo for the current run number
   int GetRunNumber() const;

   HTRunInfo *SetRunNumber(int runNum);

   bool IsDataMerged() const; //!

   const char *GetName() const;               //!
   const char *GetTitle() const;              //!
   const char *GetEvtFilePath() const;        //!
   const char *GetRootFilePath() const;       //!
   const char *GetMappedRootFilePath() const; //!

   void Clear(); //!

protected:
   HTExperimentInfo();  //! Constructor
   ~HTExperimentInfo(); //! Destructor

private:
   static HTExperimentInfo *_instance;

   std::string *fDAQConfigurationFileName;
   std::string *fPedestalFileName;
   std::string *fMappingFileName;
   std::string *fRunEvtFilePath;
   std::string *fRunTitle;

   bool fDataMerged;
   std::string fExperimentName;
   std::string fExperimentTitle;
   std::string fEvtFilePath;
   std::string fUnpackedRootFilePath;
   std::string fMappedRootFilePath;

   int fFirstRun;
   int fLastRun;
   int _runNum;
   HTRunInfo *_runInfo;

   void ParseSetConfigLine(
      const char *); //! Parse a configuration line containing the command "set" and extract Experiment info

   void ParseSetConfigLineRunInfo(const char *,
                                  int); //! Parse a configuration line containing the command "set" and extract Run info

   const char *
   RetrieveRunTitleFromEvtFile(const char *) const; //! Returns run title taken from the evt file given as input

   void
   StoreRunTitleInDatabaseFile(const char *,
                               int); //! Save run title into database file. The file takes the name of the experiment.

   int RetrieveRunTitlesFromDatabaseFile(); //! Retrieves all the run title from the database file storing into
                                            //! fRunTitle. The missing run titles are then retrieved from evt files.
};

#endif
