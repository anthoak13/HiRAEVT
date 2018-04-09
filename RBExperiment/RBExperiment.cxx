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
: type0Tree(0),type1Tree(0),type2Tree(0),type3Tree(0),type4Tree(0),type5Tree(0),type6Tree(0){
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
//#ifdef RBA1900CLASS_FLAG
////  A1900::Class()->IgnoreTObjectStreamer();
//  theA1900             = new A1900();
//  theA1900HistoManager = new A1900HistoManager();
//#endif
//#ifdef RBS800CLASS_FLAG
////  theS800             = new RBS800();
////  theS800HistoManager = new A1900HistoManager();
//#endif
#ifdef EPICSCLASS_FLAG
  TEpics::Class()->IgnoreTObjectStreamer();
  epics  = new TEpics();
#endif
#ifdef SCALERCLASS_FLAG
  TScaler::Class()->IgnoreTObjectStreamer();
  TScalerCh::Class()->IgnoreTObjectStreamer();
  scalers = new TScaler();
#endif

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

  delete header;
#ifdef EPICSCLASS_FLAG
  delete epics;
#endif
#ifdef SCALERCLASS_FLAG
  delete scalers;
#endif
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

#ifdef EPICSCLASS_FLAG
  if(kEpicsFill)  epics->Clear();
#endif
#ifdef SCALERCLASS_FLAG
  if(kScalerFill) scalers->Clear();
#endif
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

  Char_t   cBuf[200];
  sprintf(cBuf,"%u",stateItem->GetRunNumber());
  runNumber->SetTitle(cBuf);
  runTitle->SetTitle(stateItem->GetRunTitle());

  struct tm *tptr;
  time_t tstamp(stateItem->GetTimestamp());
  tptr = gmtime(&tstamp);
  dateTimestamp->SetTitle(asctime(gmtime(&tstamp)));
  sprintf(cBuf,"%i:%i:%i",tptr->tm_hour,tptr->tm_min,tptr->tm_sec);
  timeBegin->SetTitle(cBuf);
  sprintf(cBuf,"%02i.%02i.%i",tptr->tm_mon,tptr->tm_mday,tptr->tm_year + 1900);
  dateBegin->SetTitle(cBuf);
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

#ifdef SCALERCLASS_FLAG
  if(kScalerFill) scalers->DumpScalers("RUNDUMP.dat","UPDATE");
#endif

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

#ifdef EPICSCLASS_FLAG
  epics->InitClass();
#endif
#ifdef SCALERCLASS_FLAG
  scalers->InitClass();
#endif
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

#ifdef EPICSCLASS_FLAG
    if(kEpicsFill){
      if(strcmp(fChain->ClassName(),"TChain")!=0){
        epics->InitTree((TTree*)fChain->GetDirectory()->FindObjectAny("stateVarT"));
      }
    }
#endif
#ifdef SCALERCLASS_FLAG
    if(kScalerFill){
      if(strcmp(fChain->ClassName(),"TChain")!=0){
        scalers->InitTree((TTree*)fChain->GetDirectory()->FindObjectAny("scalerT"));
      }
      scalers->fEChain = fChain;
    }
#endif
}


//______________________________________________________________________________
Bool_t RBExperiment::InitializeROOTConverter(const Char_t *evtFile, const Char_t *rootFile, Option_t *nBufs)
{
  // -- Initialize the TTrees and etc. for EVT file conversion.
  //

  TString evtFileStr(evtFile);
  TSTring evtFileName(evtFileStr.SubString(evtFileStr.Last("/")+1));
  // Determine run number from file name.
  TString runNumStr(evtFileStr.SubString(evtFileStr.First("run-"),4));
  Int_t runNum = runNumStr.Atoi();

  // Determine the evt file number.
  TString evtNumStr(evtFileStr.SubString(evtFileStr.Last("-")+1,evtFileStr.Last(".evt")-evtFileStr.Last("-")-1));
  fEvtFileNumber = evtNumStr.Atoi();

  Char_t   cBuf[200];

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
  if(!fEvtFile.is_open()){ printf("File %s could not be opened!\n", evtFile); return kFALSE;}

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
  sprintf(tempChar,"E%s",expNumber->GetTitle());
  type0Tree = new TTree("stateT",     "State transition items TTree            ",2);
  type1Tree = new TTree(tempChar,     "Physics event items:  RBExperiment TTree",2);
  type2Tree = new TTree("scalerT",    "Incremental scaler items TTree          ",2);
  type3Tree = new TTree("testListT",  "Text list items TTree                   ",2);
  type4Tree = new TTree("eventCountT","Event count items TTree                 ",2);
  type5Tree = new TTree("unknownT",   "Unknown item type TTree                 ",2);

  // Initialize the branches for EVB RingItem data.
  type1Tree->Branch("fBRI_Size",     &fBRI_Size,     "fBRI_Size/i");
  type1Tree->Branch("fBRI_Timestamp",&fBRI_Timestamp,"fBRI_Timestamp/l");
  // Initialize the branches for the elctronics.
  TIter nextModule(fElectronics);
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    cout << "RBExperiment: " << elc->GetBranchName() << " " << elc->GetFillData() << endl;
    if(elc->GetFillData()) elc->InitBranch(type1Tree);
  }

#ifdef EPICSCLASS_FLAG
  if(kEpicsFill)  type4Tree->Branch("epics","TEpics",&epics);
#endif
#ifdef SCALERCLASS_FLAG
  if(kScalerFill) type2Tree->Branch("scalers","TScaler",&scalers);
#endif

//  type1Tree->SetAutoSave(50000000);

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
Int_t RBExperiment::Fill(Int_t type)
{
  // -- Fill the TTrees for a given event-item type.
  //

  if     (type==0) type0Tree->Fill();
  else if(type==1) type1Tree->Fill();
  else if(type==2) type2Tree->Fill();
  else if(type==3) type3Tree->Fill();
  else if(type==4) type4Tree->Fill();
  else if(type==5) type5Tree->Fill();
//  else if(type==6) type6Tree->Fill();
  else cerr << "-->RBExperiment::Fill Invalid event-item type." << endl;

  return type;
}

Bool_t RBExperiment::EndROOTConverter()
{
  //______________________________________________________________________________
  cout << "Read " << fBuffers << " buffers." << endl;

//  sprintf(cBuf,"%llu",fBuffers);
//  nBuffers->SetTitle(cBuf);
//  type1Tree->GetUserInfo()->Add(nBuffers);

  Char_t   cBuf[200];
//  Double_t timeTmp = atof(type1Tree->GetUserInfo()->FindObject("Elapsed Run Time")->GetTitle());
  sprintf(cBuf,"%llu",nTotEntities);
  nTotalEntities->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotType1Entities);
  nTotalType1Entities->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotWords);
  nTotalWords->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotType1Words);
  nTotalType1Words->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotEntities/timeTmp);
//  avgEventRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotType1Entities/timeTmp);
//  avgType1EventRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotWords/timeTmp);
//  avgWordRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotType1Words/timeTmp);
//  avgType1WordRate->SetTitle(cBuf);
  sprintf(cBuf,"%lli",(Long64_t)fEvtFileSize);
  evtSize->SetTitle(cBuf);
  sprintf(cBuf,"%lli",(Long64_t)fROOTFile->GetSize());
  rootSize->SetTitle(cBuf);
  type1Tree->GetUserInfo()->Add(nTotalEntities);

  type1Tree->GetUserInfo()->Add(runNumber);
  type1Tree->GetUserInfo()->Add(runTitle);
  type1Tree->GetUserInfo()->Add(expNumber);
  type1Tree->GetUserInfo()->Add(analysisState);
  type1Tree->GetUserInfo()->Add(dateTimestamp);
  type1Tree->GetUserInfo()->Add(dateBegin);
  type1Tree->GetUserInfo()->Add(timeBegin);

  type1Tree->GetUserInfo()->Add(nTotalWords);
  type1Tree->GetUserInfo()->Add(avgEventRate);
  type1Tree->GetUserInfo()->Add(avgWordRate);
  type1Tree->GetUserInfo()->Add(nTotalType1Entities);
  type1Tree->GetUserInfo()->Add(nTotalType1Words);
  type1Tree->GetUserInfo()->Add(avgType1EventRate);
  type1Tree->GetUserInfo()->Add(avgType1WordRate);
  type1Tree->GetUserInfo()->Add(evtSize);
  type1Tree->GetUserInfo()->Add(rootSize);


//  type1Tree->SetBranchStatus("*",1);
  type0Tree->AutoSave();
  type1Tree->AutoSave();
  type2Tree->AutoSave();
  type3Tree->AutoSave();
  type4Tree->AutoSave();
  type5Tree->AutoSave();
//  type6Tree->AutoSave();

//  type0Tree->Write();
//  type1Tree->Write();
//  type2Tree->Write();
//  type3Tree->Write();
//  type4Tree->Write();
//  type5Tree->Write();

  ResetTrees();

  // Write the histos.
  //  theA1900HistoManager->GetHistos()->Write("",2);

  fROOTFile->Close();
  delete fROOTFile;

  return kTRUE;

}

//______________________________________________________________________________
Bool_t RBExperiment::ConvertEvtFile(const Char_t *evtFile, const Char_t *rootFile,Option_t *nBufs)
{
  // -- Convert an NSCL (non-ringbuffer) event file to a ROOT file.
  // An event file is opened for reading and a root file created for writing.
  // A buffer is read and each entitiy in the buffer is looped over.  The buffer
  // header is read and the buffer type is determined.
  //
  // NOTE:  If the root file already exist it will be overwritten!!!
  //
  // For additional information on the buffer structure please see,
  // http://docs.nscl.msu.edu
  //

  // char holders
  Char_t tempChar[500], pathE[500], pathR[500];

  InitializeROOTConverter(evtFile, rootFile, nBufs);

  // Open evt file for reading.
  fEvtFile.open(pathE,ios::in | ios::binary);
  if(!fEvtFile.is_open()){ printf("File could not be opened!\n"); return kFALSE;}

  // Start the counter.
  time(&start);

  Char_t   cBuf[200];

  // Unpack the event file.
  while (!fEvtFile.eof()) {                  // Read event file
    UShort_t *p;                             // This is the pointer to the buffer.
    UShort_t buffer[4096];                   // 4096 16-bit unsigned-integer words.
    UShort_t packetTag;                      // packet ID number.

    fEvtFile.read((Char_t*)buffer,sizeof(buffer));   // Read buffer

    // Unpack the header              // Set the BufferHeader data members
    nWords      = buffer[0];          header->nwds = nWords;
    type        = buffer[1];          header->type = type;
    checksum    = buffer[2];
    runNum      = buffer[3];
    sequence[0] = buffer[4];
    sequence[1] = buffer[5];          header->sequence  = (Long64_t)(sequence[1]<<16|sequence[0]);
    nEntities   = buffer[6];          header->nEntities = nEntities;
    format      = buffer[10];

    nReadWords    = 1;
    nTotEntities += nEntities;
    nTotWords    += nWords;
    if(type==1){
      nTotType1Entities += nEntities;
      nTotType1Words    += nWords;
    }
#ifdef DEBUG
    cout << "Found nWords: " << nWords
    << " \t type: "     << type << " " << header->type
    << " \t checksum: " << checksum
    << " \t runNum: "      << runNum
    << " \t sequence[0]: " << sequence[0]
    << " \t sequence[1]: " << sequence[1]
    << " \t nEntities: "   << nEntities << endl;
#endif

    // Output progress to stdout.
#ifndef DEBUG
    if(counter == 50){
      time(&now);
      cent = 100 * ((Long64_t)(fBuffers * 8192))/(fEvtFileSize);
      sprintf(tempChar,"%02.2f",cent);
      cout << "Processing Buffer: " << fBuffers << "  " << tempChar << "%"
      << "   " << difftime(now, start) << " s" << "\r";
      cout.flush();
      counter=0;
    }
    counter++;
#endif

    type0Tree->Fill();

    //######################################################################
    // Event Data Type
    //######################################################################
    if (type == 1){                                // type = 1 is event data.
      p = &buffer[16];                             // Point p toward the first word after buffer header.

      for (Long64_t jj=0; jj<nEntities; jj++){     // Loop through all entities in the buffer.
        entitySize  = *p++;                        // First word in the buffer, it's the entity size.
        entitySize--;                              // The word count is self inclusive.
        nReadWords++;
        Bool_t foundEvents = kFALSE;

        while (entitySize>0) {                     // Loop through single events in the buffer.
          subEvtSize       = *p++;                 // Sub-Event length.
          subEvtLength     = subEvtSize;
          nReadWords++;

          packetTag = *p++;

          switch(packetTag){
            case A1900_PACKET:
              nReadWords++;
              foundEvents = kTRUE;
//              if(kA1900Fill) theA1900->Unpack(p);
              break;
            default:
              cout << "Uknown Packet:  " << *p <<endl;
              break;
          }

          entitySize -= subEvtLength;
          p          += subEvtLength - 2;             // Advance the pointer to the next packet. Subtract 2
                                                      // since pointer was left at begining of packet body.
          if (foundEvents == kFALSE) return kTRUE;    // Give up. We should account for all packets.
        }
        // END OF EVENT

        type1Tree->Fill();
        // Fill histos.
//        theA1900HistoManager->FillHistos(theA1900);
        // Clear all classes for next event.
        Clear();
      }
    }
    //######################################################################
    // Scaler Data Type
    //######################################################################
    else if (type == 2){ // Scaler data buffers
      // Point p toward nEntities.  This is the number of scalers read out.
      p = &buffer[6];
#ifdef SCALERCLASS_FLAG
      if(kScalerFill) {scalers->Unpack(p); type2Tree->Fill();}
#endif
      // END OF EVENT
      Clear();

    }else if (type == 3){ // Snapshot Scaler data buffers
      type3Tree->Fill();
      Clear();
    }else if (type == 4){
      type4Tree->Fill();
      Clear();
    }
    //######################################################################
    // Documentation Data Type:  Run State Variables
    //######################################################################
    else if (type == 5){ // Documentation Buffer
      // Point p toward nEntities.  This is the number of items read out.
      p = &buffer[6];
#ifdef EPICSCLASS_FLAG
      if(kEpicsFill) {epics->Unpack(p); type5Tree->Fill();}
#endif
      // END OF EVENT
      Clear();

    }else if (type == 6){
      type6Tree->Fill();
      Clear();
    }else if (type == 10){
      Clear();
    }
    //######################################################################
    // BEGIN RUN BUFFER
    //######################################################################
    else if (type == 11){ cout << "BEGIN RUN"  << endl;
      sprintf(cBuf,"%u",buffer[3]);
      runNumber->SetTitle(cBuf);

      Char_t runTitleA[200];
      Char_t *runT;
      memset(runTitleA,'\0',200);

      // Get the run title (80 bytes of 8bit char with \0 termination)
      for(Int_t i=16,j=0; i<56; i++){
        runTitleA[j]   = (Char_t)(buffer[i]&0x00ff);
        runTitleA[j+1] = (Char_t)(buffer[i]>>8);
        if(runTitleA[j+1] == '\0') break;

        j = j + 2;
      }
      runT = runTitleA;
      printf("Run Title:         %s\n",runT);

      sprintf(cBuf,"%s",runTitleA);
      runTitle->SetTitle(cBuf);
      sprintf(cBuf,"%02u/%02u/%u",buffer[58],buffer[59],buffer[60]);
      dateBegin->SetTitle(cBuf);
      sprintf(cBuf,"%02u:%02u:%02u",buffer[61],buffer[62],buffer[63]);
      timeBegin->SetTitle(cBuf);

      type1Tree->GetUserInfo()->Add(runNumber);
      type1Tree->GetUserInfo()->Add(runTitle);
      type1Tree->GetUserInfo()->Add(expNumber);
      type1Tree->GetUserInfo()->Add(analysisState);
      type1Tree->GetUserInfo()->Add(dateBegin);
      type1Tree->GetUserInfo()->Add(timeBegin);

      Clear();
    }
    //######################################################################
    // END RUN BUFFER
    //######################################################################
    else if (type == 12){ cout << endl << "END RUN"  << endl;
      // Write run info to the tree.
      if(!fRunEnd){
        // Get the elapsed runtime.
        ULong64_t  upper,lower,eTime;
        Double_t eVal;
        lower = (ULong64_t)buffer[56];
        upper = (ULong64_t)buffer[57];
        eTime = (ULong64_t)(upper<<16|lower);
        eVal  = (Double_t) eTime/10.00;                     // Convert from 10ths of seconds.
        sprintf(cBuf,"%.2lf",eVal);
        elapsedTime->SetTitle(cBuf);

        sprintf(cBuf,"%02u/%02u/%u",buffer[58],buffer[59],buffer[60]);
        dateEnded->SetTitle(cBuf);
        sprintf(cBuf,"%02u:%02u:%02u",buffer[61],buffer[62],buffer[63]);
        timeEnded->SetTitle(cBuf);
        sprintf(cBuf,"%u",fPauses);
        nPauses->SetTitle(cBuf);
        sprintf(cBuf,"%u",fResumes);
        nResumes->SetTitle(cBuf);

        type1Tree->GetUserInfo()->Add(elapsedTime);
        type1Tree->GetUserInfo()->Add(dateEnded);
        type1Tree->GetUserInfo()->Add(timeEnded);
        type1Tree->GetUserInfo()->Add(nPauses);
        type1Tree->GetUserInfo()->Add(nResumes);
      }
      //      type1Tree->Fill();
      Clear();

      if(fRunEnd) break;

      fRunEnd = kTRUE;

    }else if (type == 13){ cout << "PAUSE RUN"  << endl;
      fPauses++;
      Clear();
    }else if (type == 14){ cout << "RESUME RUN" << endl;
      fResumes++;
      Clear();
    }else{
      cout << "Buffer corrupted.  No valid data type." <<endl;
      break;
    }
    fBuffers++;

    // If nBufs is given then stop conversion.
    if(fnBuf2Read==(Long64_t)fBuffers) break;
  }

  // If run did not end correctly.
  if(!fRunEnd){
    printf("WARNING!!!  END RUN BUFFER NOT FOUND.  Run may be corrupt.\n");
    type1Tree->GetUserInfo()->Add(elapsedTime);
    type1Tree->GetUserInfo()->Add(dateEnded);
    type1Tree->GetUserInfo()->Add(timeEnded);
    type1Tree->GetUserInfo()->Add(nPauses);
    type1Tree->GetUserInfo()->Add(nResumes);
  }

  cout << "Read " << fBuffers << " buffers." << endl;

  sprintf(cBuf,"%llu",fBuffers);
  nBuffers->SetTitle(cBuf);
  type1Tree->GetUserInfo()->Add(nBuffers);

  //Double_t timeTmp = atof(type1Tree->GetUserInfo()->FindObject("Elapsed Run Time")->GetTitle());
  sprintf(cBuf,"%llu",nTotEntities);
  nTotalEntities->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotType1Entities);
  nTotalType1Entities->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotWords);
  nTotalWords->SetTitle(cBuf);
  sprintf(cBuf,"%llu",nTotType1Words);
  nTotalType1Words->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotEntities/timeTmp);
//  avgEventRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotType1Entities/timeTmp);
//  avgType1EventRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotWords/timeTmp);
//  avgWordRate->SetTitle(cBuf);
//  sprintf(cBuf,"%.2f",(Double_t)nTotType1Words/timeTmp);
//  avgType1WordRate->SetTitle(cBuf);
  sprintf(cBuf,"%lli",(Long64_t)fEvtFileSize);
  evtSize->SetTitle(cBuf);
  sprintf(cBuf,"%lli",(Long64_t)fROOTFile->GetSize());
  rootSize->SetTitle(cBuf);
  type1Tree->GetUserInfo()->Add(nTotalEntities);

  type1Tree->GetUserInfo()->Add(nTotalWords);
  type1Tree->GetUserInfo()->Add(avgEventRate);
  type1Tree->GetUserInfo()->Add(avgWordRate);
  type1Tree->GetUserInfo()->Add(nTotalType1Entities);
  type1Tree->GetUserInfo()->Add(nTotalType1Words);
  type1Tree->GetUserInfo()->Add(avgType1EventRate);
  type1Tree->GetUserInfo()->Add(avgType1WordRate);
  type1Tree->GetUserInfo()->Add(evtSize);
  type1Tree->GetUserInfo()->Add(rootSize);


  type1Tree->SetBranchStatus("*",1);
  type0Tree->AutoSave();
  type1Tree->AutoSave();
  type2Tree->AutoSave();
  type3Tree->AutoSave();
  type4Tree->AutoSave();
  type5Tree->AutoSave();
  type6Tree->AutoSave();

  fEvtFile.close();

  ResetTrees();

  // Write the histos.
  //  theA1900HistoManager->GetHistos()->Write("",2);

  fROOTFile->Close();
  delete fROOTFile;

  return kTRUE;
}

//______________________________________________________________________________
Bool_t RBExperiment::ConvertEvtFile(const Char_t *evtFileList)
{
  // -- Convert multiple event files to ROOT files.
  // Note that the argument of this method is the name of a file containing the
  // names of the event files to be converted.  IT SHOULD NOT CONTAIN THE FULL
  // PATH!!!  The location of the event files is set by calling the method
  // SetEventFilePath().

  Char_t evtFile[200];
  Char_t rootFile[200];

  ifstream listFile(evtFileList,ios::in);

  cout << "#################################################################" << endl;
  while(!listFile.eof()){
    memset(evtFile,'\0',200);
    memset(rootFile,'\0',200);
    listFile.getline(evtFile,200);

    for(Int_t i=0; i<200; i++){
      if(evtFile[i]=='.') break;
      rootFile[i] = evtFile[i];
    }
    strcat(rootFile,".root");
    cout << evtFile << " " << rootFile << endl;

    if(ConvertEvtFile(evtFile,rootFile)){
      cout << "SUCCESS!!!" << endl;
      cout << "#################################################################" << endl;
    }else{
      cout << "FAILED!!!" << endl;
      cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
    }
  }

  listFile.close();

  return kTRUE;
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
  // Must call GetUserInfo()->Clear() since deleting the tree will attempt
  // to delete the objects associated with the GetUserInfo TList.
  type0Tree->GetUserInfo()->Clear();
  type1Tree->GetUserInfo()->Clear();
  type2Tree->GetUserInfo()->Clear();
  type3Tree->GetUserInfo()->Clear();
  type4Tree->GetUserInfo()->Clear();
  type5Tree->GetUserInfo()->Clear();
//  type6Tree->GetUserInfo()->Clear();
  type0Tree->Delete();
  type1Tree->Delete();
  type2Tree->Delete();
  type3Tree->Delete();
  type4Tree->Delete();
  type5Tree->Delete();
//  type6Tree->Delete();
}


//______________________________________________________________________________
Long64_t RBExperiment::LoadTree(Long64_t entry)
{
  // -- Load an entry for a TChain.
  //

  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  //   hira->fChain->LoadTree(entry);
  //   for(Int_t i=0; i<16; i++) hira->tele[i].fChain->LoadTree(entry);
  //   for(Int_t i=0; i<16; i++) hira->tele[i].EF.fChain->LoadTree(entry);

  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
  }
  return centry;
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
