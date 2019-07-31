#ifndef HTMAPPER_H
#define HTMAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <HTExperimentalSetup.h>
#include <HTExperimentInfo.h>
#include <HTRunInfo.h>

class HTMapper
{
public :
  HTMapper();                                  //! Constructor
  ~HTMapper();                                 //! Destructor

  int PassArguments(int, char **);             //! Retrieves run number to analyze. Returns -1 if run number is not found

  TTree * GetRawTree() const;                  //! Returns a pointer to the TTree containing data to map
  TTree * GetMappedTree() const;               //! Returns a pointer to the TTree containing mapped data

  int InitializeMapper(const char *);          //! Called at the beginning of the entire mapping process. Returns -1 if failed to build experimental setup, returns -2 if failed to open output file, returns -3 if failed to load experiment info
  int LoadExperimentInfo(const char *);        //! Initialize experiment info
  int BuildExperimentalSetup();                //! Initialize ExperimentalSetup. Returns -1 if failed to allocate experimental setup, -2 falied to build modules, -3 failed to build detectors, -4 failed to build detector map
  int InitRootOutput();                        //! Initialize ROOT TTree and TFile for output

  void MapDetectors();                         //! Called Event-by-event by HTDataReader
  void FillMappedEvent();                      //! Called Event-by-event after mapping detectors by HTDataReader
  void EndMapping();                           //! Called at the end of the entire mapping process by HTDataReader

private :
  TTree * fMappedTree;                         //! TTree with mapped data
  TFile * fFileOut;                            //! TFile for output
  int fRunNumber;                              //! Run number to analyze

};

#endif
