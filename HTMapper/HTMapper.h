#ifndef HTMAPPER_H
#define HTMAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include <HTExperimentalSetup.h>

class HTMapper
{
public :
  HTMapper();                                  //! Constructor
  ~HTMapper();                                 //! Destructor

  int InitializeMapper();                      //! Called at the beginning of the entire mapping process
  int LoadExperimentInfo(const char *);        //! Initialize experiment info
  void BuildExperimentalSetup();               //! Initialize ExperimentalSetup
  int InitRootOutput();                        //! Initialize ROOT TTree and TFile for output

  void MapDetectors();                         //! Called Event-by-event
  void FillMappedEvent();                      //! Called by MapDetectors after mapping detectors
  void EndMapping();                           //! Called at the end of the entire mapping process

private :
  TTree * fMappedTree;                         //! TTree with mapped event
  TFile * fFileOut;                            //! TFile for output
  HTExperimentalSetup * fExpSetup;             //! Experimental Setup

};

#endif
