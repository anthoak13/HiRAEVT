//
//  RBExperiment.cpp
//
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//  Modified by Daniele Dell'Aquila (April 2018)
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

ClassImp(RBExperiment);
ClassImp(RBNSCLBufferHeader);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML
 <p> RBExperiment provides the structure for holding a typical
 experiment at the NSCL.  For each device a class is constructed.
 For example there is a class that represents HiRA (RBHiRA) and the
 S800 (RBS800).  An instance of  these classes is then instanciated in
 RBExperiment.</p>

 <p>RBExperiment is then a contruct that describes the entire experiment.   </p>

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
: fRunNumber(-1),fEvtFileNumber(-1),fRootTree(0),fBuffers(0),fnTotEntities(0),fnTotWords(0){
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
  expTitle            = new TNamed("Experiment Title",gExperimentInfo->GetTitle());
  expNumber           = new TNamed("Experiment Number",gExperimentInfo->GetName());
  runTitle            = new TNamed("Run Title",gRun->GetTitle());
  runNumber           = new TNamed("Run Number",Form("%d",gRun->GetRunNumber()));
  evtFileNumber       = new TNamed("Evt File Number","");
  dateTimestamp       = new TNamed("Date timestamp Begin","");
  dateBegin           = new TNamed("Run Begin Date","");
  timeBegin           = new TNamed("Run Begin Time","");
  dateEnd             = new TNamed("Run End Date","");
  timeEnd             = new TNamed("Run End Time","");
  evtSize             = new TNamed("Event File Size","");
  rootSize            = new TNamed("ROOT File Size","");

  //Set merged data flag (taken from Andy's code Aug 19 2016)
  SetMergedData(kFALSE);
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
  // -- Obsolete
}

//______________________________________________________________________________
void RBExperiment::DumpClassInfo()
{
  // -- Obsolete
  //
}

//______________________________________________________________________________
void RBExperiment::SetStateInfo(RBRingStateChangeItem * stateItem)
{
  // -- This method sets additional information to TTRee UserInfo objects
  //    dateTimestamp
  //    timeBegin
  //    dateBegin
  struct tm *tptr;

  if(strcmp(stateItem->GetType(),"Unknown (1)")==0) { //run begin
    time_t tstamp(stateItem->GetTimestamp());
    tptr = gmtime(&tstamp);
    dateTimestamp->SetTitle(asctime(gmtime(&tstamp)));
    timeBegin->SetTitle(Form("%02d:%02d:%02d",tptr->tm_hour,tptr->tm_min,tptr->tm_sec));
    dateBegin->SetTitle(Form("%02d.%02d.%4d",tptr->tm_mon,tptr->tm_mday,tptr->tm_year + 1900));
  } else if(strcmp(stateItem->GetType(),"Unknown (2)")==0) { //run end
    time_t tstamp(stateItem->GetTimestamp());
    tptr = gmtime(&tstamp);
    timeEnd->SetTitle(Form("%02d:%02d:%02d",tptr->tm_hour,tptr->tm_min,tptr->tm_sec));
    dateEnd->SetTitle(Form("%02d.%02d.%4d",tptr->tm_mon,tptr->tm_mday,tptr->tm_year + 1900));
  }
}

//______________________________________________________________________________
void RBExperiment::DumpInfo()
{
  // -- Obsolete
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
TTree * RBExperiment::GetTree()
{
  return fRootTree;
}

//______________________________________________________________________________
Bool_t RBExperiment::InitializeROOTConverter(const Char_t *evtFile, const Char_t *rootFile, Option_t *nBufs)
{
  // -- Initialize the TTree for EVT file conversion.
  //
  std::string evtFileStr(evtFile);
  std::string evtFileName(evtFileStr.substr(evtFileStr.find_last_of('/')+1));

  // Setting run number
  fRunNumber = gRun->GetRunNumber();

  // Determine the evt file number.
  std::string evtNumStr(evtFileStr.substr(evtFileStr.find_last_of('-')+1,evtFileStr.find(".evt")-evtFileStr.find_last_of('-')-1));
  fEvtFileNumber = atoi(evtNumStr.c_str());

  // Set the number of buffers to unpack.
  fnBuf2Read = (Long64_t)atoi(nBufs);

  // Set the path for the root file.
  TString rootFileStr(rootFile);
  if(rootFileStr=="out.root"){
    rootFileStr.Clear();
    rootFileStr.Append(gExperimentInfo->GetRootFilePath());
    rootFileStr.Append(evtFileName);
    rootFileStr.ReplaceAll(".evt",".root");
  }

  // Open evt file for reading.
  fEvtFile.open(evtFile,ios::in | ios::binary);
  if(!fEvtFile.is_open()){printf("ERROR: File %s could not be opened!\n", evtFile); return kFALSE;}

  fEvtFile.seekg(0,ios::end);
  fEvtFileSize = fEvtFile.tellg();
  cout << "**Evt File size:        " << fEvtFileSize << " bytes **" << endl;

  // Open ROOT file for writing.
  fROOTFile = new TFile(rootFileStr.Data(),"RECREATE");

  if (fROOTFile->IsZombie()) {
    cout << "Error opening file " << rootFileStr << endl;
    exit(-1);
  }else{
    cout << "**Opened ROOT file:     " << rootFileStr << " **" << endl;
  }

  // We must be careful here.  The file must be open before we create the tree.
  fRootTree = new TTree(Form("E%s",gExperimentInfo->GetName()), gRun->GetTitle(),2);

  // Initialize the branches for EVB RingItem data.
  fRootTree->Branch("fBRI.Size",     &fBRI_Size,     "fBRI.Size/I");
  fRootTree->Branch("fBRI.Timestamp",&fBRI_Timestamp,"fBRI.Timestamp/L");
  // Initialize the branches for the elctronics.
  TIter nextModule(fElectronics);
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    if(elc->GetFillData()) {
      elc->InitBranch(fRootTree);
      cout << "**TTree Branches initialized: " << elc->GetBranchName() << " **" <<  endl;
    }
  }

  fRootTree->SetAutoSave(50000000);

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
void RBExperiment::AddTTreeUserInfo()
{
  // -- This method sets UserInfo objects to the tree
  evtSize->SetTitle(Form("%lli",(Long64_t)fEvtFileSize));
  rootSize->SetTitle(Form("%lli",(Long64_t)fROOTFile->GetSize()));
  evtFileNumber->SetTitle(Form("%d", fEvtFileNumber));

  fRootTree->GetUserInfo()->Add(expTitle);
  fRootTree->GetUserInfo()->Add(expNumber);
  fRootTree->GetUserInfo()->Add(runTitle);
  fRootTree->GetUserInfo()->Add(runNumber);
  fRootTree->GetUserInfo()->Add(evtFileNumber);
  fRootTree->GetUserInfo()->Add(dateBegin);
  fRootTree->GetUserInfo()->Add(timeBegin);
  fRootTree->GetUserInfo()->Add(dateEnd);
  fRootTree->GetUserInfo()->Add(timeEnd);
  fRootTree->GetUserInfo()->Add(evtSize);
  fRootTree->GetUserInfo()->Add(rootSize);

  //Adding summary information
  TIter nextModule(fElectronics);
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    if(elc->GetFillData()) elc->AddTTreeUserInfo(fRootTree);
  }

}

//______________________________________________________________________________
Bool_t RBExperiment::EndROOTConverter()
{
  // -- This method closes the TTree and saves the file

  fRootTree->AutoSave();

  fROOTFile->Close();
  delete fROOTFile;

  return kTRUE;

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
