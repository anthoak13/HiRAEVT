//
//  HTExperiment.h
//
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//  Modified by Daniele Dell'Aquila (April 2018)
//

#ifndef ____HTExperiment__
#define ____HTExperiment__

#include "HTExperimentInfo.h"
#include "HTRunInfo.h"
#include "HTUSBStack.h"

#include <HTElectronics.h>

#include <HTRingStateChangeItem.h>
#include <TBranch.h>
#include <TChain.h>
#include <TEventList.h>
#include <TFile.h>
#include <TFolder.h>
#include <TH2S.h>
#include <TROOT.h>
#include <TTree.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class HTExperiment : public TNamed {

private:
   //UShort_t *p; //! Pointer to event buffers.

   Int_t fRunNumber;      //! Number of the current run to be unpacked.
   Int_t fEvtFileNumber;  //! Number of the current evt file.
   Long64_t fEvtFileSize; //! Size of the evt file in bytes.
   Bool_t fMergedData;

   TList *fElectronics; //! List of registered electronics to process.

   TFile *fROOTFile;  //! The current ROOT file for output.
   TTree *fRootTree; //!

   UInt_t fBRI_Size;         //
   ULong64_t fBRI_Timestamp; //

public:
   TNamed *expNumber;     //! Experiment ID number.
   TNamed *expTitle;      //! Experiment title.
   TNamed *runTitle;      //! Run title.
   TNamed *runNumber;     //! Run number.
   TNamed *evtFileNumber; //! Evt file Number.
   TNamed *dateTimestamp; //! Date timestamp (UNIX time(2)).
   TNamed *dateBegin;     //! Run creation date.
   TNamed *timeBegin;     //! Run creation time.
   TNamed *dateEnd;       //! Run end date.
   TNamed *timeEnd;       //! Run end time.
   TNamed *evtSize;       //! Event file size.
   TNamed *rootSize;      //! Root file size.

public:
   const Char_t *evtFilePath;  //! Source of event files.
   const Char_t *rootFilePath; //! Destination of ROOT files.

   TTree *fChain;  //! Pointer to the analyzed TTree or TChain.
   Int_t fCurrent; //! Current Tree number in a TChain.

   HTExperiment(const char *name = "E000000");
   ~HTExperiment();

   // Does everything that the old HTSetup class does
   void Setup();

   void Clear(Option_t *option = "");


   void AddTTreeUserInfo();
   void Fill();      // Fill TTree

   // Initialized the TTrees and etc. for EVT file conversion.
   Bool_t InitializeROOTConverter(const Char_t *evtFile, const Char_t *rootFile = "out.root"); 
   Bool_t EndROOTConverter();
   
   HTElectronics *RegisterElectronics(HTElectronics *elc); //

   // Getters
   Bool_t IsDataMerged() { return fMergedData; } 
   Long64_t GetEvtFileSize() { return fEvtFileSize; }
   TList *GetElectronicsList() { return fElectronics; } 
   TTree *GetTree();                  
   
   //Setters
   void SetBRISize(UInt_t size) { fBRI_Size = size; }
   void SetBRITimestamp(ULong64_t tStamp) { fBRI_Timestamp = tStamp; }
   void SetMergedData(Bool_t mergedFlag) { fMergedData = mergedFlag; } // Sets the merged data flag.
   Bool_t SetEventFilePath(const Char_t *path);      // Sets the event file path.
   Bool_t SetExperimentNumber(const Char_t *number); // Sets the experiment number.
   Bool_t SetRootFilePath(const Char_t *path);       // Sets the root file path.
   void SetStateInfo(HTRingStateChangeItem *);       // Sets additional information such as run start time

   ClassDef(HTExperiment, 1) // NSCL event-data unpacker.
};

#endif /* defined(____HTExperiment__) */
