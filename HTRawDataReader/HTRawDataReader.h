#ifndef HTRAWDATAREADER_H
#define HTRAWDATAREADER_H

#include <HTMapper.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTree.h>
#include <TChain.h>
#include <ctime>
#include <map>
#include <HTExperimentalSetup.h>

class HTRawDataReader
{
public :
  HTRawDataReader(HTMapper *theMapper);    //!Constructor
  ~HTRawDataReader();                      //!Destructor

  int InitReader();                   //!Called after mapper and input tree are set to initialize input tree branches. Returns -1 if failed to create TTreeReader. -2 failed to retrieve Root input file(s)
  int InitRootInput();                //!Initialize ROOT TTree and TFile for input, returns the number of files retrieved
  void SetMapper(HTMapper *);         //!Called at the beginning of the unpacking process to set the Mapper
  void ProcessRawTree();              //!Executes event-by-event HTMapper::MapDetectors() and HTMapper::FillMappedEvent()
  void EndProcess();                  //!Called at the end of the mapping process. It calls HTMapper::EndMapping()
  void PrintSummary();                //!Print Mapping summary

private :
  HTMapper * fDataMapper;             //!the mapper
  TChain * fDataTree;                 //!tree with raw data
  int fNEvtFiles;                     //!Number of evt files in the run
  TTreeReader *fDataReader;           //!TTreeReader object to read data from fDataTree
  unsigned long long fTotalEvents;    //!Total events to map
  unsigned long long fCurrEvent;      //!Current Event to map
  time_t fStart;                      //!Mapping process start time
  time_t fNow;                        //!Current processing time
  double fTimeElapsed;                //!Total elapsed time for Raw tree process

};

#endif
