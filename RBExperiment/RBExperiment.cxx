//
//  RBExperiment.cpp
//
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//

#include "RBExperiment.h"

#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <iostream>

#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TEventList.h>
#include <TNamed.h>
#include <time.h>
#include <sys/stat.h>

#ifndef __PACKETID_H
#define __PACKETID_H
#include "packetID.h"
#endif

ClassImp(RBExperiment);
ClassImp(RBNSCLBufferHeader);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML
 <p> RBExperiment provides the structure for holding a typical
 experiment at the NSCL.  For each device a class is constructed.
 For example there is a class that represents HiRA (RBHiRA) and the
 S800 (RBS800).  An instance of  these classes is then instanciated in
 RBExperiment.</p>

 <p>RBExperiment is then a contruct that describes the entire experiment.   </p

 <p>Run information can be displayed using the command,
 tree->GetUserInfo()->Print()
 This information can also be stored and used in any processing
 scripts written for this tree.  For example, to get the number of times
 the run was paused we could do,
 Char_t *ch;
 ch = (Char_t*)tree->GetUserInfo->FindObject("Pauses")->GetTitle();
 </p>
 <h3><a name="unpack">I. Unpacking</a></h3>

 <h3><a name="vars">II. Important Data Members</a></h3>

 <h3><a name="examples">III. Examples</a></h3>


 END_HTML */
////////////////////////////////////////////////////////////////////////////////


//______________________________________________________________________________
RBExperiment::RBExperiment(const char *name)
: fRunNumber(-1),fEvtFileNumber(-1),fRootTree(0),fBuffers(0){
  // -- Default constructor.
  // If a sub-class inherits from TObject and you do not want the fBits and
  // fUniqueID to be streamed out to the root file then it is advisable to
  // add the line,
  //              MyClass::Class()->IgnoreTObjectStreamer();
  // This will save, in some cases, a significant amount of disk space when
  // writing a root file.

  fName = name;

  // Create the electronics list.
  fElectronics = new TList();

  RBNSCLBufferHeader::Class()->IgnoreTObjectStreamer();

  // Allocate memory for objects that will be written to UserInfo list.
  analysisState       = new TNamed("Analysis State","-1");
  expNumber           = new TNamed("Experiment Number","unknown");
  runTitle            = new TNamed("Run Title","");
  runNumber           = new TNamed("Run Number","");
  dateTimestamp       = new TNamed("Date timestamp","");
  elapsedTime         = new TNamed("Elapsed Run Time","");
  dateBegin           = new TNamed("Run Begin Date","");
  dateEnded           = new TNamed("Run End Date","");
  timeBegin           = new TNamed("Run Begin Time","");
  timeEnded           = new TNamed("Run End Time","");
  nPauses             = new TNamed("Pauses","-1");
  nResumes            = new TNamed("Resumes","-1");
  nBuffers            = new TNamed("Number of buffers read","-1");

  nTotalEntities      = new TNamed("Total Entity Count","-1");
  nTotalType1Entities = new TNamed("Total Type1 (Data) Entity Count","-1");
  nTotalWords         = new TNamed("Total Word Count","-1");
  nTotalType1Words    = new TNamed("Total Type1 (Data) Word Count","-1");
  avgEventRate        = new TNamed("Average Event Rate","-1");
  avgType1EventRate   = new TNamed("Average Type1 (Data) Event Rate","-1");
  avgWordRate         = new TNamed("Average Word Rate","-1");
  avgType1WordRate    = new TNamed("Average Type1 (Data) Word Rate","-1");
  evtSize             = new TNamed("Event File Size","-1");
  rootSize            = new TNamed("ROOT File Size","-1");


  evtFilePath  = "./";
  rootFilePath = "./";

  // Allocate memory for detector classes. (?)
  header = new RBNSCLBufferHeader();

  //Set merged data flag (taken from Andy's code Aug 19 2016)
  SetMergedData(kFALSE);

  // By default do not fill anything.
  kA1900Fill   = kFALSE;
  kS800Fill    = kFALSE;
  kEpicsFill   = kFALSE;
  kScalerFill  = kFALSE;
  kElogFill    = kFALSE;

}


//______________________________________________________________________________
RBExperiment::~RBExperiment()
{
  // --  Destructor
  //
}

//______________________________________________________________________________
RBElectronics* RBExperiment::RegisterElectronics(RBElectronics *elc)
{
  // -- Register and add the electronic module to the list of modules (fElectronics).
  fElectronics->AddLast(elc);
  return elc;
}

//______________________________________________________________________________
void RBExperiment::Clear(Option_t *option)
{
  // -- Clear all member classes.
  //
  fBRI_Size      = 0;
  fBRI_Timestamp = 0;

  header->Clear();

  TIter nextModule(fElectronics);
  while(RBElectronics* elc = (RBElectronics*)nextModule()){
    elc->Clear(option);
  }
}

//______________________________________________________________________________
void RBExperiment::CreateFolders()
{
  // -- Create all initial folders.
  // Folders can be useful for storing global constants, calibration file data,
  // run information . . . among other things.
  //
  // This method should call all sub-class CreateFolders methods.
}

//______________________________________________________________________________
void RBExperiment::SetRunInfo(RBRingStateChangeItem *stateItem)
{
  // --
  //
  runNumber->SetTitle(Form("%u",stateItem->GetRunNumber()));
  runTitle->SetTitle(stateItem->GetRunTitle());

  struct tm *tptr;
  time_t tstamp(stateItem->GetTimestamp());
  tptr = gmtime(&tstamp);
  dateTimestamp->SetTitle(asctime(gmtime(&tstamp)));
  timeBegin->SetTitle(Form("%i:%i:%i",tptr->tm_hour,tptr->tm_min,tptr->tm_sec));
  dateBegin->SetTitle(Form("%02i.%02i.%i",tptr->tm_mon,tptr->tm_mday,tptr->tm_year + 1900));
}

//______________________________________________________________________________
void RBExperiment::DumpClassInfo()
{
  // -- Output of currently built and fillable classes.
  //

  printf("**********************DUMPING CLASS MEMBERS INFO*****************************\n");
  Bool_t kBuilt=kFALSE;

#ifdef EPICSCLASS_FLAG
  kBuilt=kTRUE;
#endif
  printf("* TEpics Class Built . . .     [%u] \t Filled . . . [%u]\n",kBuilt,kEpicsFill);
  kBuilt=kFALSE;
#ifdef SCALERCLASS_FLAG
  kBuilt=kTRUE;
#endif
  printf("* TScaler Class Built . . .    [%u] \t Filled . . . [%u]\n",kBuilt,kScalerFill);
  kBuilt=kFALSE;
#ifdef ELOGCLASS_FLAG
  kBuilt=kTRUE;
#endif
  printf("* TElog Class Built . . .      [%u] \t Filled . . . [%u]\n",kBuilt,kElogFill);
  kBuilt=kFALSE;
}


//______________________________________________________________________________
void RBExperiment::DumpInfo()
{
  // -- Output all run information.
  // This output should include all information in the UserInfoList of the current TTree.
  // In addition scaler values are output along with any quantities calculated with these
  // values.

  ofstream dumpFile("RUNDUMP.dat",ios::out);
  Char_t outC[2000];

  printf("***************************DUMPING RUN INFO**********************************\n");

  // Dump UserInfo
  fChain->GetUserInfo()->Print();
  TNamed *namedTmp = (TNamed*)fChain->GetUserInfo()->FindObject("Elapsed Run Time");
  if(namedTmp){
    Double_t eTime   = atof(namedTmp->GetTitle());
    TNamed *dumpN;
    TIter next(fChain->GetUserInfo());
    while((dumpN = (TNamed *)next())){
      sprintf(outC,"%-35.35s \t%s\n",dumpN->GetName(),dumpN->GetTitle());
      dumpFile << outC;
    }
  }
  dumpFile.close();

}


//______________________________________________________________________________
void RBExperiment::InitClass()
{
  // -- Initialize the class and sub-classes.
  // The InitClass method of all member classes should be called here.  This
  // method is responsible for setting all the defaults of the member classes.

  TIter nextModule(fElectronics);
  while(RBElectronics* elc = (RBElectronics*)nextModule()){
    elc->InitClass();
  }
}


//______________________________________________________________________________
void RBExperiment::InitTree(TTree *itree)
{
  // -- Initialze a tree.
  // Set the branch addresses for all members of all classes.
  //
  // IMPORTANT:  This method assumes that classes are created using the object oriented
  //             method described in the ROOT Users Manual or that the corresponding
  //             class has a valid InitTree method.

  fChain = itree;

  TIter nextModule(fElectronics);
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    if(elc->GetFillData()) elc->InitTree(fChain);
  }
}


//______________________________________________________________________________
Bool_t RBExperiment::InitializeROOTConverter(const Char_t *evtFile, const Char_t *rootFile, Option_t *nBufs)
{
  // -- Initialize the TTrees and etc. for EVT file conversion.
  //
  std::string evtFileStr(evtFile);
  std::string evtFileName(evtFileStr.substr(evtFileStr.find_last_of('/')+1));
  // Determine run number from file name.
  std::string runNumStr(evtFileStr.substr(evtFileStr.find("run-")+4,4));
  fRunNumber = atoi(runNumStr.c_str());

  // Determine the evt file number.
  std::string evtNumStr(evtFileStr.substr(evtFileStr.find_last_of('-')+1,evtFileStr.find(".evt")-evtFileStr.find_last_of('-')-1));
  fEvtFileNumber = atoi(evtNumStr.c_str());

  // Set the number of buffers to unpack.
  fnBuf2Read = (Long64_t)atoi(nBufs);

  // Set the path for the root file.
  TString rootFileStr(rootFile);
  if(rootFileStr=="out.root"){
    rootFileStr.Clear();
    rootFileStr.Append(rootFilePath);
    rootFileStr.Append(evtFileName);
    rootFileStr.ReplaceAll(".evt",".root");
  }

  // Open evt file for reading.
  fEvtFile.open(evtFile,ios::in | ios::binary);
  if(!fEvtFile.is_open()){printf("File %s could not be opened!\n", evtFile); return kFALSE;}

  fEvtFile.seekg(0,ios::end);
  fEvtFileSize = fEvtFile.tellg();
  cout << "Evt File size:        " << fEvtFileSize << " bytes" << endl;

  // Open ROOT file for writing.
  fROOTFile = new TFile(rootFileStr.Data(),"RECREATE");

  if (fROOTFile->IsZombie()) {
    cout << "Error opening file " << rootFileStr << endl;
    exit(-1);
  }else{
    cout << "Opened ROOT file:     " << rootFileStr << endl;
  }

  // We must be careful here.  The file must be open before we create the tree.
  fRootTree = new TTree(Form("E%s",expNumber->GetTitle()), "RIBbitUnpacker Tree created by RIBbit2",2);

  // Initialize the branches for EVB RingItem data.
  fRootTree->Branch("fBRI.Size",     &fBRI_Size,     "fBRI.Size/I");
  fRootTree->Branch("fBRI.Timestamp",&fBRI_Timestamp,"fBRI.Timestamp/L");
  // Initialize the branches for the elctronics.
  TIter nextModule(fElectronics);
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    cout << "RBExperiment: " << elc->GetBranchName() << " " << elc->GetFillData() << endl;
    if(elc->GetFillData()) elc->InitBranch(fRootTree);
  }

//  fRootTree->SetAutoSave(50000000);

//  CreateFolders();

  analysisState->SetTitle("0");  // Set the analysis state to 0=RAW data TTree.

  fBuffers          = 0;
  nTotEntities      = 0;
  nTotType1Entities = 0;
  nTotWords         = 0;
  nTotType1Words    = 0;
  nBuffers->SetTitle("0");
  nTotalEntities->SetTitle("0");
  nTotalType1Entities->SetTitle("0");
  nTotalWords->SetTitle("0");
  nTotalType1Words->SetTitle("0");

  counter  = 0 ;                  // Counter for updating progress.
  fPauses  = 0;                   // Number of times run was paused.
  fResumes = 0;                   // Number of times run was resumed.
  fRunEnd  = kFALSE;              // Did we find an end run buffer?

  // Close file and open later during convsersion process.
  fEvtFile.close();

  return kTRUE;
}

//______________________________________________________________________________
void RBExperiment::Fill()
{
  // -- Fill the TTrees for a given event-item type.
  //

  fRootTree->Fill();
}

//______________________________________________________________________________
Bool_t RBExperiment::EndROOTConverter()
{
  // -- Obsolete

  return kFALSE;

}

//______________________________________________________________________________
Bool_t RBExperiment::ConvertEvtFile(const Char_t *evtFile, const Char_t *rootFile,Option_t *nBufs)
{
  // -- Not anymore used

  return kFALSE;
}

//______________________________________________________________________________
Bool_t RBExperiment::ConvertEvtFile(const Char_t *evtFileList)
{
  // -- Not anymore used

  return kFALSE;
}


//______________________________________________________________________________
Bool_t RBExperiment::ConvertRingBufferEvtFile(const Char_t *evtFile, const Char_t *rootFile, Option_t *nBufs)
{
  // -- NOT implemented through ROOT currently

  return kFALSE;
}

//______________________________________________________________________________
void RBExperiment::ResetTrees()
{
  // -- Obsolete
}


//______________________________________________________________________________
Long64_t RBExperiment::LoadTree(Long64_t entry)
{
  // -- Obsolete
  return 0;
}


//______________________________________________________________________________
Bool_t RBExperiment::SetEventFilePath(const Char_t *path)
{
  // -- Sets the event file source path.
  // This is the location from which event files will be read.
  evtFilePath = path;
  return kTRUE;
}


//______________________________________________________________________________
Bool_t RBExperiment::SetExperimentNumber(const Char_t *number)
{
  // -- Sets the experiment number of this instance of RBExperiment.
  expNumber->SetTitle(number);
  return kTRUE;
}


//______________________________________________________________________________
Bool_t RBExperiment::SetRootFilePath(const Char_t *path)
{
  // -- Sets the root file destination path.
  // Any root file generated from an event file will be written to this directory.

  rootFilePath = path;

  return kTRUE;
}
