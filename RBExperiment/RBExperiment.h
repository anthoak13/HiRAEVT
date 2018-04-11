//
//  RBExperiment.h
//
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//

#ifndef ____RBExperiment__
#define ____RBExperiment__

#include <iostream>

#include "RBNSCLBufferHeader.h"

//#include "RBA1900.h"
//#include "RBA1900HistoManager.h"
//class A1900HistoManager;

#include "RBRingStateChangeItem.h"
#include "RBElectronics.h"


//#ifdef SCALERCLASS_FLAG
//#include  "TScaler.h"
//#endif

#include <fstream>
#include <string>

#include <TChain.h>
#include <TFile.h>
#include <TBranch.h>
#include <TEventList.h>
#include <TFolder.h>
#include <TH2S.h>
#include <TROOT.h>
#include <TTree.h>

using namespace std;

class RBExperiment : public TNamed {

private:
  UShort_t *p;                                      //! Pointer to event buffers.

  Int_t       fRunNumber;                           //! Number of the current run to be unpacked.
  Int_t       fEvtFileNumber;                       //! Number of the current evt file.
  Long64_t    fEvtFileSize;                         //! Size of the evt file in bytes.
  Long64_t    fnBuf2Read;                           //! Number of buffers to unpack.

  Bool_t      fMergedData;

  ifstream    fEvtFile;                             //! The current EVT file.
  TFile      *fROOTFile;                            //! The current ROOT file for output.

  TList      *fElectronics;                         //! List of registered electronics to process.

  TTree      *fRootTree;                            //!

  // Buffer properties
  UShort_t nWords;               //! Number of used words in the buffer.
  UShort_t type;                 //! Type of data in the buffer.
  UShort_t checksum;             //! Buffer checksum.
  UShort_t runNum;               //! Run number of active run.
  UShort_t sequence[2];          //! Buffer sequence number.
  UShort_t nEntities;            //! Number of entities or events in the buffer.
  UShort_t format;               //! Buffer format version.
  UShort_t entitySize;           //! Entity size word (self-inclusive).
  UShort_t subEvtSize;           //! Event size word (self-inclusive).

  UShort_t nReadWords;           //! Number of read words in the buffer.
  UShort_t subEvtLength;         //! Number of words in an event.

  // Read buffer statistics
  ULong64_t fBuffers;            //! Number of read buffers.
  ULong64_t nTotEntities;        //! Total number of entities of events in the run.
  ULong64_t nTotType1Entities;   //! Total number of data entities of events in the run.
  ULong64_t nTotWords;           //! Total number of words in run.
  ULong64_t nTotType1Words;      //! Total number of data words in run.

  Int_t    counter;              //! Counter for updating progress.
  Float_t  cent;                 //! Percent done.
  time_t   start;                //! Start conversion time.
  time_t   now;                  //! Current time.

  Int_t    fPauses;              //! Number of times run was paused.
  Int_t    fResumes;             //! Number of times run was resumed.
  Bool_t   fRunEnd;              //! Did we find an end run buffer?

  UInt_t    fBRI_Size;           //
  ULong64_t fBRI_Timestamp;      //


public:
  TNamed *analysisState;                            //! Number indicating current TTree analysis state. 0=RAW 1=CAL etc.

  TNamed *expNumber;                                //! Experiment ID number.
  TNamed *runTitle;                                 //! Run title.
  TNamed *runNumber;                                //! Run number.
  TNamed *dateTimestamp;                            //! Date timestamp (UNIX time(2)).
  TNamed *elapsedTime;                              //! Elapsed runtime (seconds).
  TNamed *dateBegin;                                //! Run creation date.
  TNamed *dateEnded;                                //! Run end date.
  TNamed *timeBegin;                                //! Run creation time.
  TNamed *timeEnded;                                //! Run end time.
  TNamed *nPauses;                                  //! Number of times run was paused.
  TNamed *nResumes;                                 //! Number of times run was resumed.
  TNamed *nBuffers;                                 //! Total number of Buffers.
  TNamed *nTotalEntities;                           //! Total number of entities.
  TNamed *nTotalType1Entities;                      //! Total number of data entities.
  TNamed *nTotalWords;                              //! Total number of used words.
  TNamed *nTotalType1Words;                         //! Total number of used data words.
  TNamed *avgEventRate;                             //! Average number of events/s.
  TNamed *avgType1EventRate;                        //! Average number of data events/s.
  TNamed *avgWordRate;                              //! Average number of words/s.
  TNamed *avgType1WordRate;                         //! Average number of data words/s.
  TNamed *evtSize;                                  //! Event file size.
  TNamed *rootSize;                                 //! Root file size.
  TNamed *runType;                                  //! Run type.
  TNamed *runComments;                              //! Run Comments.
  TNamed *primaryBeam;                              //! Primary beam.
  TNamed *secondaryBeam;                            //! Secondary beam.
  TNamed *primaryEnergy;                            //! Primary beam energy.
  TNamed *secondaryEnergy;                          //! Secondary beam energy.
  TNamed *note;                                     //! Run note.
  TObjArray notesArray;                             //! Array to hold run notes.

  Bool_t  kA1900Fill;                               //! A1900 fill flag.
  Bool_t  kS800Fill;                                //! S800 fill flag.
  Bool_t  kEpicsFill;                               //! Epics fill flag.
  Bool_t  kScalerFill;                              //! Scaler fill flag.
  Bool_t  kElogFill;                                //! Elog fill flag.

  TFolder f_constants;                              //!
  TFolder f_scaler;                                 //!

public:
  const Char_t *evtFilePath;                        //! Source of event files.
  const Char_t *rootFilePath;                       //! Destination of ROOT files.

  RBNSCLBufferHeader *header;                            //  Buffer header class.

//  A1900             *theA1900;              //!
//  A1900HistoManager *theA1900HistoManager;  //!

  TTree         *fChain;                //! Pointer to the analyzed TTree or TChain.
  Int_t          fCurrent;              //! Current Tree number in a TChain.

private:
//  Bool_t ConvertRingBufferEvt(Char_t *evtFile, Char_t *rootFile,
//                              Option_t *nBufs="0");

public:
  RBExperiment() {RBExperiment("E00000");}
  RBExperiment(const char *name);
  ~RBExperiment();

  void         Clear(Option_t *option="");
  Bool_t       ConvertEvtFile(const Char_t *evtFile,
                              const Char_t *rootFile,
                              Option_t *nBufs="0");               // Converts an event file to root.
  Bool_t       ConvertRingBufferEvtFile(const Char_t *evtFile,
                                        const Char_t *rootFile,
                                        Option_t *nBufs="0");     // Converts a ring buffer event file to root.
  Bool_t       ConvertEvtFile(const Char_t *evtFileList);               // Converts a list of event files.
  void         CreateFolders();                                   // Create all folders.
  void         DumpInfo();                                        // Dump event info.
  void         DumpClassInfo();                                   // Dump class build and fill info.
  Bool_t       EndROOTConverter();
  void         Fill();                                            // Fill TTree
  void         InitClass();                                       // Calls all InitClass methods.
  Bool_t       InitializeROOTConverter(const Char_t *evtFile,
                                       const Char_t *rootFile="out.root",
                                       Option_t *nBufs="0");      // Initialized the TTrees and etc. for EVT file conversion.
  void         InitTree(TTree *itree);
  Long64_t     LoadTree(Long64_t entry);                          //
  void         ResetTrees();                                      // Clear TTrees UserInfo and delete objects.

  RBElectronics*  RegisterElectronics(RBElectronics *elc);        //

  Bool_t       IsDataMerged()      {return fMergedData;}          //

  Long64_t     GetEvtFileSize()    {return fEvtFileSize;}
  ULong64_t    GetReadBuffers()    {return fBuffers;}             //
  TList*       GetElectronicsList(){return fElectronics;}         //

  void         SetBRISize(UInt_t size){fBRI_Size = size;}
  void         SetBRITimestamp(ULong64_t tStamp){fBRI_Timestamp = tStamp;}

  void         SetMergedData(Bool_t mergedFlag){fMergedData = mergedFlag;} // Sets the merged data flag.

  void         SetRunInfo(RBRingStateChangeItem *stateItem);      //
  Bool_t       SetEventFilePath(const Char_t *path);                    // Sets the event file path.
  Bool_t       SetExperimentNumber(const Char_t *number);               // Sets the experiment number.
  Bool_t       SetRootFilePath(const Char_t *path);                     // Sets the root file path.

  ClassDef(RBExperiment,1)     // NSCL event-data unpacker.
};

#endif /* defined(____RBExperiment__) */
