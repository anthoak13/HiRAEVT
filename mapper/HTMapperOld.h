#ifndef HTMAPPER_H
#define HTMAPPER_H

// This class manages the mapper. It loads the passed config file, sets up the input and output ROOT files.

#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class HTMapper {
public:
   HTMapper();  //! Constructor
   ~HTMapper(); //! Destructor

   int PassArguments(int, char **); //

   TTree *GetRawTree() const;    //! Returns a pointer to the TTree containing data to map
   TTree *GetMappedTree() const; //! Returns a pointer to the TTree containing mapped data

   int InitializeMapper(const char *);   //! Called at the beginning of the entire mapping process. Returns -1 if failed
                                         //! to build experimental setup, returns -2 if failed to open output file,
                                         //! returns -3 if failed to load experiment info
   int LoadExperimentInfo(const char *); //! Initialize experiment info
   int
   BuildExperimentalSetup(); //! Initialize ExperimentalSetup. Returns -1 if failed to allocate experimental setup, -2
                             //! falied to build modules, -3 failed to build detectors, -4 failed to build detector map
   int InitRootOutput();     //! Initialize ROOT TTree and TFile for output

   void MapDetectors();    //! Called Event-by-event by HTDataReader
   void FillMappedEvent(); //! Called Event-by-event after mapping detectors by HTDataReader
   void EndMapping();      //! Called at the end of the entire mapping process by HTDataReader

private:
   TTree *fMappedTree; //! TTree with mapped data
   TFile *fFileOut;    //! TFile for output
   int fRunNumber;     //! Run number to analyze
};

#endif