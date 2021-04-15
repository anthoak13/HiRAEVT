
#include <FragmentIndex.h>
#include <HTExperiment.h>
#include <HTExperimentInfo.h>
#include <HTRunInfo.h>
#include <TFile.h>
#include <TH1.h>
#include <TList.h>
#include <TNamed.h>
#include <TString.h>
#include <TTree.h>
#include <Unpacker.h>
#include <iomanip>
#include <iostream>

//______________________________________________________________________________
Unpacker::Unpacker() : nevent(0), fReadWords(0), fTimeElapsed(0), m_lastTimestamp(0), fDebug(0)
{
   // --
   //
   Clear();
}

//______________________________________________________________________________
Unpacker::Unpacker(const Unpacker &rhs)
{
   // --
   //
}

//______________________________________________________________________________
Unpacker::~Unpacker()
{
   // --
   //
}

//______________________________________________________________________________
void Unpacker::Clear()
{
   // --
   //

   fTimestampMismatch = 0;
   fFoundTimestampMismatch = kFALSE;
}

//______________________________________________________________________________
void Unpacker::InitializeUnpacker(char *sourceName)
{
   // --
   // Here the following objects are initialized:
   // gRun : HTRunInfo class object containing all the info for the current run
   // fExperiment : HTExperiment class object containing stack configurations and defining the structure of the output
   // file
   //
   
   strcpy(fSourceFileName, sourceName);
   std::string evtFileStr(fSourceFileName);
   std::string evtFileName(evtFileStr.substr(evtFileStr.find_last_of('/') + 1));
   auto confVal = std::getenv("HiRAEVTCONFIG");

   if (confVal == nullptr) {
      cout << "Envirment not configured for config file" << endl;
      exit(-1);
   }

   std::string configFile(confVal);

   // Determine run number from file name.
   std::string runNumStr(evtFileStr.substr(evtFileStr.find("run-") + 4, 4));

   int RunNumber = atoi(runNumStr.c_str());
   int EvtFileNumber = atoi(
      evtFileStr
         .substr(evtFileStr.find_last_of("-") + 1, evtFileStr.find_last_of(".") - (evtFileStr.find_last_of("-") + 1))
         .c_str());

   // Initialization of HTRunInfo class
   cout << "** Initializing Run Info for run " << RunNumber << " **" << endl;

   cout << "Loading config file: " << configFile << endl;

   if (HTExperimentInfo::Instance()->InitClass(configFile.c_str()) <= 0) {
      cout << "Error while reading configuration file.\n";
      exit(-1);
   }

   auto runInfo = HTExperimentInfo::Instance()->SetRunNumber(RunNumber);

   cout << "** Run Info correctly initialized **\n";

   fExperiment = new HTExperiment();
   fExperiment->Setup();

   if (fExperiment == 0) {
      cout << "Failed to initalize experiment electronics." << endl;
      exit(-1);
   }

   fMergedData = fExperiment->IsDataMerged();

   fExperiment->InitializeROOTConverter(fSourceFileName);

   fExperiment->Clear("A");
   fStart = clock();

   printf("** Unpacking run %d-%02d : %s **\n", runInfo->GetRunNumber(), EvtFileNumber, runInfo->GetTitle());
}

//______________________________________________________________________________
void Unpacker::operator()(uint64_t eventTimestamp, uint32_t sourceId, uint32_t barrierType, std::string typeName,
                          uint32_t runNumber, uint32_t timeOffset, time_t timestamp, std::string title)
{

   // --
   //
   HTRingStateChangeItem stateItem(eventTimestamp, sourceId, barrierType, typeName, runNumber, timeOffset, timestamp,
                                   title);

   fExperiment->SetStateInfo(&stateItem);
}

//______________________________________________________________________________
void Unpacker::operator()(FragmentIndex &index, uint32_t totalSize, uint64_t eventTimestamp)
{
   // -- Call the individual detector unpackers and pass along the FragmentIndex.
   // Each detector unpacker should handle looking for it's own type identifier and
   // proceed with it's unpacker.
   //
   // NOTE: We really should change this to loop over all Sources where each source contains
   // detectors, electronics, and etc..

   ++nevent;

   // cout << "**Unpacking timestamp " << eventTimestamp<< endl;

   // Display progress
   if (nevent % 10000 == 0) {
      PrintPercentage();
   }

   fExperiment->Clear();

   fExperiment->SetBRISize(totalSize);
   fExperiment->SetBRITimestamp(eventTimestamp);

   // Create iterators to loop through all the fragments
   FragmentIndex::iterator it, begin, end;
   begin = index.begin();
   end = index.end();

   // Iterate through the fragments
   it = begin;
   while (it != end) {
      // Define an offset to keep track of where we the fragment is located
      // and to check that we are unpacking all the data in the buffer.
      UInt_t fragOffset = 0;

      // Let's keep track of the total words that we read.
      UInt_t totalReadWords = 0;

      // Check the timestamps.
      if (it->s_timestamp < m_lastTimestamp) {
         fTimestampMismatch++;
         if (fFoundTimestampMismatch) {
            std::cout << "Found out of order timestamp at event " << nevent << std::endl;
            fFoundTimestampMismatch = kTRUE; // Further msgs will be supressed.
         }
      }

      // Reset the last timestamp.
      m_lastTimestamp = it->s_timestamp;

      // Loop over all data sources and unpack all  . . . (Should implement it this way)

      // Loop over all registered electronic modules and call their individual Unpacker methods.
      // If we come across a USBStack, then each module is unpacked as defined in the HTUSBStack class.
      TIter nextModule(fExperiment->GetElectronicsList());
      while (HTElectronics *elc = (HTElectronics *)nextModule()) {
         //      cout << "Module is " << elc->GetBranchName() << endl;

         // Check if the Merged ID matches that of the current module.

         if (it->s_sourceId == elc->GetMergedID()) {
            // Workaround for old EVB bug to only process physics events
            uint32_t type = *(it->s_itemhdr + 2);
            uint16_t *bodyDebugAddr = it->s_itemhdr;
            // Make sure this is a PHYSICS_EVENT item.
            if (type == 30) {
               uint32_t ringSize = *(it->s_itemhdr);


               //--- Print out the RingItem. -----------------
               if (false) {
                  cout << "RingSize = " << ringSize / 2 << " " << index.getNumberFragments() << endl;
                  for (int dd = 1; dd <= ringSize / 2; dd++) {
                     printf("%0.4x ", *bodyDebugAddr++);
                     if (dd % 5 == 0 && dd != 0)
                        cout << "-- " << dd << endl;
                  }
                  cout << endl;
               }
               //--------------------------------------------------

               // This is actually the pointer to the RingItem body header.
               uint16_t *bodyAddr = it->s_itembody;

               // Unpack it
               fragOffset =  static_cast<HTUSBStack*>(elc)->Unpack(bodyAddr, 0);
               // totalUnpackedWords += elc->GetTotalUnpackedWords();
            } else {
               cerr << "-->Unpacker::operator This is not a PHYSICS_EVENT item." << endl;
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
   fExperiment->Fill(); // This unpacker handles PHYSICS event items.

   // Update the counters.
   fReadWords += totalSize / 2;
}

//______________________________________________________________________________
void Unpacker::operator()(uint16_t *pBody, uint32_t totalSize, uint64_t eventTimestamp)
{
   ++nevent;

   // Display progress
   if (nevent % 10000 == 0) {
      PrintPercentage();
   }

   fExperiment->Clear();

   fExperiment->SetBRISize(totalSize);
   fExperiment->SetBRITimestamp(eventTimestamp);

   // Check the timestamps.
   if (eventTimestamp < m_lastTimestamp) {
      fTimestampMismatch++;
      if (fFoundTimestampMismatch) {
         std::cout << "Found out of order timestamp at event " << nevent << std::endl;
         fFoundTimestampMismatch = kTRUE; // Further msgs will be supressed.
      }
   }

   // Reset the last timestamp.
   m_lastTimestamp = eventTimestamp;

   // Verify that the data does not look corrupted
   UShort_t bodySize = *pBody;
   if (2 * (bodySize + 1) != totalSize) {
      std::cerr << "The first word should represent the number of words composing the event"
		  << std::endl;
      fReadWords += totalSize;
      return;
   }
   if (totalSize <= 2) {
      std::cerr << "Only one word present in event, skipping" << std::endl;
      fReadWords += totalSize;
      return;
   }
   if (pBody[bodySize] != 0xFFFF) {
      std::cerr << "The event buffer must terminate with 0xFFFF, skipping" << std::endl;
      fReadWords += totalSize;
      return;
   }

   // Let's keep track of the total words that we read.
   UInt_t totalReadWords = 0;

   TIter nextModule(fExperiment->GetElectronicsList());
   while (HTElectronics *elc = (HTElectronics *)nextModule())
   {
      UInt_t readWords = static_cast<HTUSBStack*>(elc)->Unpack(pBody, 0);
      *pBody += readWords;
      totalReadWords += readWords;
   }
   // Finished with this event,
   // now fill the TTrees with the data we just unpacked.
   fExperiment->Fill(); // This unpacker handles PHYSICS event items.

   // Update the counters.
   fReadWords += totalSize / 2;
}

// unpack a longword from the event array...assumption is that localhost is
// little endian.

unsigned long Unpacker::getLong(std::vector<unsigned short> &event, unsigned int offset)
{
   unsigned long low = event[offset];
   unsigned long hi = event[offset + 1];

   return low | (hi << 16);
}

//______________________________________________________________________________
void Unpacker::PrintSummary()
{

   // -- This method print a general final summary of the unpacking procedure
   cout << "\n\n--Unpacking summary--" << endl;
   printf("Unpacking time : %.0f s\n", fTimeElapsed);
   printf("%llu events unpacked\n", nevent);
   printf("%llu words read\n", fReadWords);
   printf("%llu timestamp mismatches found\n", fTimestampMismatch);
   printf("--End of Unpacking--\n\n");

   TIter nextModule(fExperiment->GetElectronicsList());
   while (HTElectronics *elc = (HTElectronics *)nextModule())
      elc->PrintSummary();
}

//______________________________________________________________________________
void Unpacker::AddTTreeUserInfo(TTree *tree)
{
   TNamed *elapsedTime = new TNamed("Unpacking Time", Form("%.0f", fTimeElapsed));
   TNamed *eventsUnpacked = new TNamed("Events Unpacked", Form("%llu", nevent));
   TNamed *wordsRead = new TNamed("Words Read", Form("%llu", fReadWords));
   TNamed *timestampMismatches = new TNamed("Timestamp Mismatches", Form("%llu", fTimestampMismatch));

   tree->GetUserInfo()->Add(elapsedTime);         // Duration of the unpacking procedure
   tree->GetUserInfo()->Add(eventsUnpacked);      // Number of events unpacked
   tree->GetUserInfo()->Add(wordsRead);           // Number of words read
   tree->GetUserInfo()->Add(timestampMismatches); // Number of timestamp mismatches found
}

//______________________________________________________________________________
void Unpacker::EndUnpacking()
{
   // -- This method is called at the end of the Unpacking process
   //    It calls PrintSummary() and finally ends the ROOT conversion
   fTimeElapsed = (double)(clock() - fStart) / CLOCKS_PER_SEC;

   AddTTreeUserInfo(fExperiment->GetTree());
   fExperiment->AddTTreeUserInfo();
   fExperiment->EndROOTConverter();
   PrintSummary();
}

//____________________________________________________
void Unpacker::PrintPercentage() const
{
   double time_elapsed = (double)(clock() - fStart) / CLOCKS_PER_SEC;
   std::cout << "  Percentage= " << std::fixed << std::setprecision(1) << std::setw(5)
             << 100 * ((Long64_t)(2 * fReadWords)) / (fExperiment->GetEvtFileSize()) << " %";
   std::cout << "   [";
   int printindex = 0;
   for (; printindex < int(100 * ((Long64_t)(2 * fReadWords)) / (fExperiment->GetEvtFileSize())); printindex += 5)
      std::cout << "=";
   for (; printindex < 100; printindex += 5)
      std::cout << " ";
   std::cout << "]   "
             << "elapsed time " << std::setprecision(1)
             << (time_elapsed < 60 ? time_elapsed : (time_elapsed < 3600 ? time_elapsed / 60 : time_elapsed / 3600))
             << (time_elapsed < 60 ? " s; " : (time_elapsed < 3600 ? " m; " : " h; "));
   if (fReadWords > 2) {
      double time_remaining = (time_elapsed / (2. * fReadWords)) * (fExperiment->GetEvtFileSize() - 2 * fReadWords);
      std::cout << " estimated remaining time: " << std::setprecision(1)
                << (time_remaining < 60 ? time_remaining
                                        : (time_remaining < 3600 ? time_remaining / 60 : time_remaining / 3600))
                << (time_remaining < 60 ? " s      " : (time_remaining < 3600 ? " m      " : " h      "));
   }
   std::cout << "\r";
   std::cout.flush();
}

//____________________________________________________
void Unpacker::PrintPercentageSimple() const
{
   std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5)
             << 100 * ((Long64_t)(2 * fReadWords)) / (fExperiment->GetEvtFileSize()) << " %";
   std::cout << "   [";
   int printindex = 0;
   for (; printindex < int(100 * ((Long64_t)(2 * fReadWords)) / (fExperiment->GetEvtFileSize())); printindex += 5)
      std::cout << "=";
   for (; printindex < 100; printindex += 5)
      std::cout << " ";
   std::cout << "]   \r";
   std::cout.flush();
}
