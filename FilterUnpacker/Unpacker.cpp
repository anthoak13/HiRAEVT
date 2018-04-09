
#include "FragmentIndex.h"
#include "Unpacker.h"

#include <iostream>
#include <iomanip>

#include <TFile.h>
#include <TH1.h>
#include <TString.h>

#include "RBDetector.h"
#include "RBExperiment.h"
#include "RBSetup.h"

// Instantiate the ROOT unpacker
Unpacker gUnpacker;

//______________________________________________________________________________
Unpacker::Unpacker():nevent(0),fCounter(0),fReadWords(0),m_lastTimestamp(0),fDebug(0)
{
  // --
  //
  
  // Set the RBExperiment pointer
  fSetup = new RBSetup();
  fExperiment = fSetup->GetInitializedExp();
  if(fExperiment) cout << "Initialized experimental setup: " << fExperiment << endl;
  else            cout << "Failed to initalize experimental setup." << endl;
  
  fMergedData = fExperiment->IsDataMerged();
  
  Clear();
}


//______________________________________________________________________________
Unpacker::Unpacker(const Unpacker& rhs) 
{
  // --
  //
  
}


//______________________________________________________________________________
Unpacker::~Unpacker() 
{
  // --
  //
  
  cout << "\n\n--Unpacking summary--" << endl;
  printf("%llu events unpacked\n", nevent);
  printf("%llu words read\n", fReadWords);
  printf("%llu timestamp mismatches found\n", fTimestampMismatch);
  printf("\n");
  TIter nextModule(fExperiment->GetElectronicsList());
  while(RBElectronics *elc = (RBElectronics*)nextModule()){ //loop over the stacks
    //cout << " " << elc->GetName() << " " << elc->GetUnpackErrorCount() << endl;
    //Here we should print the error summaries for every stack in the DAQ
    elc->PrintSummary();
  }
  fExperiment->EndROOTConverter();
}


//______________________________________________________________________________
void Unpacker::Clear()
{
  // --
  //
  
  fTimestampMismatch      = 0;
  fFoundTimestampMismatch = kFALSE;
  
}

//______________________________________________________________________________
void Unpacker::SetSource(char *sourceName)
{
  // --
  //
  
  strcpy(fSourceFileName, sourceName);
  //
  fExperiment->InitializeROOTConverter(fSourceFileName);
  fExperiment->Clear("A");
  time(&fStart);
}


//______________________________________________________________________________
void Unpacker::operator() (uint64_t eventTimestamp, uint32_t sourceId,
                           uint32_t barrierType,    std::string typeName,
                           uint32_t runNumber,      uint32_t timeOffset,
                           time_t   timestamp,      std::string  title)
{
  // --
  //
  
  RBRingStateChangeItem stateItem(eventTimestamp, sourceId, barrierType, typeName,
                                  runNumber, timeOffset, timestamp, title);
  
  fExperiment->SetRunInfo(&stateItem);
}


//______________________________________________________________________________
void Unpacker::operator()(FragmentIndex& index, uint32_t totalSize, uint64_t eventTimestamp)
{
  // -- Call the individual detector unpackers and pass along the FragmentIndex.
  // Each detector unpacker should handle looking for it's own type identifier and
  // proceed with it's unpacker.
  //
  // NOTE: We really should change this to loop over all Sources where each source contains
  // detectors, electronics, and etc..
  
  ++nevent;

  //cout << "**Unpacking timestamp " << eventTimestamp<< endl;
  
  // Display progress
  char tempChar[10];
  if(fCounter == 100){
    time(&fNow);
    fPercentDone = 100 * ((Long64_t)(2*fReadWords))/(fExperiment->GetEvtFileSize());
    sprintf(tempChar,"%02.2f",fPercentDone);
    cout << "Processing Event: " << setw(10) << nevent << setw(10)
         << "  " << tempChar << "%"
         << "   " << difftime(fNow, fStart) << " s" << "\r";
    cout.flush();
    fCounter=0;
  }
  fCounter++;
  
  fExperiment->Clear();
  
  fExperiment->SetBRISize     (totalSize);
  fExperiment->SetBRITimestamp(eventTimestamp);
  
  // Create iterators to loop through all the fragments
  FragmentIndex::iterator it, begin, end;
  begin = index.begin();
  end   = index.end();
  
  // Iterate through the fragments
  it = begin;
  while(it != end){
    // Define an offset to keep track of where we the fragment is located
    // and to check that we are unpacking all the data in the buffer.
    UInt_t fragOffset = 0;
    
    // Let's keep track of the total words that we read.
    UInt_t totalReadWords = 0;
    
    // Check the timestamps.
    if (it->s_timestamp < m_lastTimestamp) {
      fTimestampMismatch++;
      if(fFoundTimestampMismatch){
        std::cout << "Found out of order timestamp at event " << nevent << std::endl;
        fFoundTimestampMismatch = kTRUE; //Further msgs will be supressed.
      }
    }
    
    // Reset the last timestamp.
    m_lastTimestamp = it->s_timestamp;
    
    // Loop over all data sources and unpack all  . . . (Should implement it this way)
    
    // Loop over all registered electronic modules and call their individual Unpacker methods.
    // If we come across a USBStack, then each module is unpacked as defined in the RBUSBStack class.
    TIter nextModule(fExperiment->GetElectronicsList());
    while(RBElectronics *elc = (RBElectronics*)nextModule()){
      //      cout << "Module is " << elc->GetBranchName() << endl;

      // Check if the Merged ID matches that of the current module.
      if (it->s_sourceId == elc->GetMergedID()) {
        // Workaround for old EVB bug to only process physics events
        uint32_t  type          = *(it->s_itemhdr+2);
        uint16_t* bodyDebugAddr = it->s_itemhdr;
        // Make sure this is a PHYSICS_EVENT item.
        if(type == 30) {
          uint32_t ringSize = *(it->s_itemhdr);
          //--- Print out the RingItem. -----------------
          if(false){
            cout << "RingSize = " << ringSize/2 << " " << index.getNumberFragments() << endl;
            for(int dd=1; dd<=ringSize/2; dd++){
              printf("%0.4x ", *bodyDebugAddr++);
              if(dd%5==0 && dd!=0) cout << "-- " << dd << endl;
            }
            cout << endl;
          }
          //--------------------------------------------------
          
          // This is actually the pointer to the RingItem body header.
          uint16_t* bodyAddr = it->s_itembody;
	  uint16_t* bodyAddrJuan = it->s_itembody;

	  //Check bodyAddr
	  //	  cout << "Check bodyAddr before skipping " << endl;
	  //	  for(int dd=1; dd<=10; dd++){
	  //	    printf("%0.4x ", bodyAddrJuan[dd-1]);
	  //	    if(dd%5==0 && dd!=0) cout << "-- " << dd << endl;
	  //	  }

	  //NOTE: THIS SKIPPING IS NO LONGER NECESSARY...THE FRAGMENT
	  //INDEXING NOW TAKES CARE OF THIS
	  
          // Skip the body header, it is 20 bytes long and we pass
          // along a pointer to the beginning of the RingItem body.
          // Read the RingItem body header.
	  //          for(Int_t skip=0; skip<10; skip++){//10
	  //	    *bodyAddr++;
	    //	    *bodyAddrJuan++;
	  //	  }

	  //Check bodyAddr
	  //	  cout << "Check bodyAddr after skipping " << endl;
	  //	  for(int dd=1; dd<=10; dd++){
	  //	    printf("%0.4x ", bodyAddrJuan[dd+9]);
	  //	    if(dd%5==0 && dd!=0) cout << "-- " << dd << endl;
	  //	  }

	  
          // Unpack it
          fragOffset = elc->Unpack(bodyAddr, 0);
          //totalUnpackedWords += elc->GetTotalUnpackedWords();
        }
        else{
          cerr << "-->Unpacker::operator This is not a PHYSICS_EVENT item." << endl;
        }
      }
    }
    
    // Loop over all registered detectors and call their individual Unpacker methods.
    TIter nextDet(fExperiment->GetDetectorList());
    while(RBDetector *det = (RBDetector*)nextDet()){
      // Map data from unpacked electronics to the detector class.
      if(det->GetFillData()) det->UnpackMappedElectronics();
      
      if (it->s_sourceId == det->GetMergedID()) {
        // workaround for old EVB bug to only process physics events
        uint32_t type = *(it->s_itemhdr+2);
        if (type == 30) {
          uint16_t* bodyAddr = it->s_itembody;
          
          // Set the fragment data of the detector.
          det->SetTimestamp(it->s_timestamp);
          
          // Unpack data using any internal detector method.
          fragOffset = det->Unpack(bodyAddr, fragOffset);
          //totalUnpackedWords += det->GetTotalUnpackedWords();
        }
      }
    }

//    std::cout << "TStamp: "    << it->s_timestamp
//              << "  SourceId: "  << it->s_sourceId
//              << "  Size: "      << it->s_size
//              << "  Barrier: "   << it->s_barrier
//              << std::endl;

    // increment our iterator
    ++it;
    
    // Check that we read all the words in the fragment.
    // If we did not, then all of the detectors/electronics may
    // no be defined.
//    if(totalUnpackedWords != it->s_size){
//      cerr << "-->Unpacker:: Total number of words in fragment was "
//           << it->s_size << " but we only unpacked " << totalUnpackedWords << endl;
//    }
  }

  // Finished with this event,
  // now fill the TTrees with the data we just unpacked.
  fExperiment->Fill(1); // This unpacker handles PHYSICS event items.
  
  // Update the counters.
  fReadWords += totalSize/2;
  
}


//______________________________________________________________________________
void Unpacker::operator()(uint16_t *pBody, uint32_t totalSize, uint64_t eventTimestamp)
{  
  // -- Call the individual detector unpackers and pass along the FragmentIndex.
  // Each detector unpacker should handle looking for it's own type identifier and
  // proceed with it's unpacker.
  //
  // NOTE: We really should change this to loop over all Sources where each source contains
  // detectors, electronics, and etc..
  
  ++nevent;
  
  // Display progress
  char tempChar[10];
  if(fCounter == 50){
    time(&fNow);
    fPercentDone = 100 * ((Long64_t)(fReadWords))/(fExperiment->GetEvtFileSize());
    sprintf(tempChar,"%02.2f",fPercentDone);
    cout << "Processing Event: " << setw(10) << nevent << setw(10)
    << "  " << tempChar << "%"
    << "   " << difftime(fNow, fStart) << " s" << "\r";
    cout.flush();
    fCounter=0;
  }
  fCounter++;
  
  fExperiment->Clear();
  
  fExperiment->SetBRISize     (totalSize);
  fExperiment->SetBRITimestamp(eventTimestamp);
  
  // Define an offset to keep track of where we the fragment is located
  // and to check that we are unpacking all the data in the buffer.
  UInt_t fragOffset = 0;
  
  // Let's keep track of the total words that we read.
  UInt_t totalReadWords = 0;
  
  // Check the timestamps.
  if (eventTimestamp < m_lastTimestamp) {
    fTimestampMismatch++;
    if(fFoundTimestampMismatch){
      std::cout << "Found out of order timestamp at event " << nevent << std::endl;
      fFoundTimestampMismatch = kTRUE; //Further msgs will be supressed.
    }
  }
    
  // Reset the last timestamp.
  m_lastTimestamp = eventTimestamp;
    
  // Loop over all data sources and unpack all  . . . (Should implement it this way)
  
  // Loop over all registered electronic modules and call their individual Unpacker methods.
  // If we come across a USBStack, then each module is unpacked as defined in the RBUSBStack class.
  TIter nextModule(fExperiment->GetElectronicsList());
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    // Check if the Merged ID matches that of the current module.
//    if (it->s_sourceId == elc->GetMergedID()) {
      // Workaround for old EVB bug to only process physics events
//      uint32_t  type          = *(it->s_itemhdr+2);
//      uint16_t* bodyDebugAddr = it->s_itemhdr;
      // Make sure this is a PHYSICS_EVENT item.
//      if(type == 30) {
//        uint32_t ringSize = *(it->s_itemhdr);
//        //--- Print out the RingItem. -----------------
//        if(false){
//          cout << "RingSize = " << ringSize/2 << " " << index.getNumberFragments() << endl;
//          for(int dd=1; dd<=ringSize/2; dd++){
//            printf("%0.4x ", *bodyDebugAddr++);
//            if(dd%5==0 && dd!=0) cout << "-- " << dd << endl;
//          }
//          cout << endl;
//        }
        //--------------------------------------------------
        
//        // This is actually the pointer to the RingItem body header.
//        uint16_t* bodyAddr = it->s_itembody;
//        
//        // Skip the body header, it is 20 bytes long and we pass
//        // along a pointer to the beginning of the RingItem body.
//        // Read the RingItem body header.
//        for(Int_t skip=0; skip<10; skip++) *bodyAddr++;
    
        // Unpack it
//    *pBody++;
    fragOffset = elc->Unpack(pBody, 0);
        //totalUnpackedWords += elc->GetTotalUnpackedWords();
//      }
//      else{
//        cerr << "-->Unpacker::operator This is not a PHYSICS_EVENT item." << endl;
//      }
//    }
  }
  
    // Loop over all registered detectors and call their individual Unpacker methods.
    TIter nextDet(fExperiment->GetDetectorList());
    while(RBDetector *det = (RBDetector*)nextDet()){
      // Map data from unpacked electronics to the detector class.
      if(det->GetFillData()) det->UnpackMappedElectronics();
      
//      if (it->s_sourceId == det->GetMergedID()) {
        // workaround for old EVB bug to only process physics events
//        uint32_t type = *(it->s_itemhdr+2);
//        if (type == 30) {
//          uint16_t* bodyAddr = it->s_itembody;
      
          // Set the fragment data of the detector.
          det->SetTimestamp(eventTimestamp);
          
          // Unpack data using any internal detector method.
      *pBody++;
          fragOffset = det->Unpack(pBody, fragOffset);
          //totalUnpackedWords += det->GetTotalUnpackedWords();
//        }
//      }
    }
    
    //    std::cout << "TStamp: "    << it->s_timestamp
    //              << "  SourceId: "  << it->s_sourceId
    //              << "  Size: "      << it->s_size
    //              << "  Barrier: "   << it->s_barrier
    //              << std::endl;
    
    // increment our iterator
//  ++it;
  
    // Check that we read all the words in the fragment.
    // If we did not, then all of the detectors/electronics may
    // no be defined.
    //    if(totalUnpackedWords != it->s_size){
    //      cerr << "-->Unpacker:: Total number of words in fragment was "
    //           << it->s_size << " but we only unpacked " << totalUnpackedWords << endl;
    //    }
//}

  // Finished with this event,
  // now fill the TTrees with the data we just unpacked.
  fExperiment->Fill(1); // This unpacker handles PHYSICS event items.
  
  // Update the counters.
  fReadWords += totalSize;
  
}

//______________________________________________________________________________
void Unpacker::operator()(uint16_t *pBody, uint32_t totalSize)
{
  // -- Unpack non-merged data.
  //
  ++nevent;

  //  cout << "**Unpacking timestamp " << eventTimestamp<< endl;
  
  // Display progress
  char tempChar[10];
  if(fCounter == 1000){
    time(&fNow);
    fPercentDone = 100 * ((Long64_t)(fReadWords))/(fExperiment->GetEvtFileSize());
    
    sprintf(tempChar,"%02.2f",fPercentDone);
    cout << "Processing Event: " << setw(10) << nevent << setw(10)
         << "  " << tempChar << "%"
         << "   " << difftime(fNow, fStart) << " s" << "\r";      
    
    cout.flush();
    fCounter=0;
  }
  fCounter++;
  
  fExperiment->Clear();
  
  fExperiment->SetBRISize     (totalSize);
  //  fExperiment->SetBRITimestamp(eventTimestamp);
  
  //  UShort_t bodySize = *pBody++;
  //Note: I commented out the line above because the HINPUnpacker was starting one word too late
  //...not sure whether or not this has something to do with a one word difference between
  //unpacking merged data vs unmerged data.
  UShort_t bodySize = *pBody;
  if(2*(bodySize+1)!=totalSize) {
    //WARNING: the first word should represent the number of word composing the event
    fReadWords += totalSize;
    return;    
  }
  if(bodySize==0 || totalSize<=2) {
    //WARNING: bodySize can be 0, in such a case the event is bad and has to be skipped!
    //WARNING: sometimes only 1 word is present in the event (totalSize=2) -> skip the event.
    fReadWords += totalSize;
    return;
  }  
  if(pBody[*pBody] != 0xFFFF) {
    //WARNING: the event buffer must terminate with 0xFFFF
    fReadWords += totalSize;
    return;    
  }
  //  cout << "Body size is " << bodySize << endl;
  //  UShort_t hdrSize  = *pBody;
  //  cout << "Header size is " << hdrSize << endl;
  // Loop over all registered electronics modules and call their individual Unpacker methods.
  TIter nextModule(fExperiment->GetElectronicsList());
  
  
  UInt_t readWords = 0;
  while(RBElectronics *elc = (RBElectronics*)nextModule()){
    
    // unpack it
    //    cout << "Unpacking electronics " << elc->GetBranchName() << endl;
    //    cout << "Value of pBody address going into elc Unpack: " << *pBody << endl;
    readWords = elc->Unpack(pBody,0);
    while(readWords>0){*pBody++; readWords--;}
  }

  //Now loop over all registered detectors and call individual unpackers
  TIter nextDet(fExperiment->GetDetectorList());
  while(RBDetector *det = (RBDetector*)nextDet()){
    // Map data from unpacked electronics to the detector class.
    if(det->GetFillData()){
      //cout << "Unpacking HiRA" << endl;
      det->UnpackMappedElectronics();
    }
    // Unpack data using any internal detector method.
    //    readWords = det->Unpack(bodyAddr);
    //totalUnpackedWords += det->GetTotalUnpackedWords();
  }

  fExperiment->Fill(1);

  fReadWords += totalSize;
}


// unpack a longword from the event array...assumption is that localhost is
// little endian.

unsigned long
Unpacker::getLong(std::vector<unsigned short>& event,
                          unsigned int offset)
{
  unsigned long low = event[offset];
  unsigned long hi  = event[offset+1];
  
  
  return low | (hi << 16);
}

