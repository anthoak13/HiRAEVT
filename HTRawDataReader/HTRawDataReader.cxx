#include <HTRawDataReader.h>

//________________________________________________
HTRawDataReader::HTRawDataReader(HTMapper *theMapper)
   : fDataMapper(theMapper), fDataTree(0), fNEvtFiles(0), fDataReader(0), fTotalEvents(0), fCurrEvent(0), fStart(0),
     fNow(0), fTimeElapsed(0)
{
}

//________________________________________________
HTRawDataReader::~HTRawDataReader()
{
   if (fDataReader)
      delete fDataReader;
}

//________________________________________________
int HTRawDataReader::InitReader()
{
   // Opening input TFile and TTree to read data
   if (InitRootInput() <= 0)
      return -2;

   printf("** Correctly retrieved %d evt file(s) for mapping from folder %s **\n", fNEvtFiles,
          HTExperimentInfo::Instance()->GetRootFilePath());

   // Seting TTreeReader to the opened TChain
   fDataReader = new TTreeReader(fDataTree);
   if (!fDataTree)
      return -1;

   // Loop on the modules retrieved from HTExperimentalSetup::Instance() to init their individual TTreeReader Branches
   auto DefinedModules = HTExperimentalSetup::Instance()->GetModules();
   for (auto TheModule : *DefinedModules) {
      TheModule.second->InitTreeInputBranch(*fDataReader);
      printf("TTreeReader: Correctly recognized module %s\n", TheModule.second->GetName());
   }

   return 0;
}

//________________________________________________
int HTRawDataReader::InitRootInput()
{
   // Opening a new TFile for input
   fDataTree = new TChain(Form("E%s", HTExperimentInfo::Instance()->GetName()));
   fNEvtFiles = fDataTree->Add(Form("%srun-%04d-*.root", HTExperimentInfo::Instance()->GetRootFilePath(),
                                    HTExperimentInfo::Instance()->GetRunInfo()->GetRunNumber()));
   fTotalEvents = fDataTree->GetEntries();
   return fNEvtFiles;
}

//________________________________________________
void HTRawDataReader::SetMapper(HTMapper *theMapper)
{
   fDataMapper = theMapper;
}

//________________________________________________
void HTRawDataReader::ProcessRawTree()
{
   time(&fStart);

   while (fDataReader->Next()) {
      // Display progress
      if (fCurrEvent % 1000 == 0) {
         time(&fNow);
         fTimeElapsed = difftime(fNow, fStart);
         double PercentDone = 100 * (double(fCurrEvent) / fTotalEvents);
         std::cout << "Processing Event: " << setw(10) << fCurrEvent << setw(10) << "  " << Form("%02.2f", PercentDone)
                   << "%"
                   << "   " << fTimeElapsed << " s"
                   << "\r";
         std::cout.flush();
      }

      // Map all the detectors
      fDataMapper->MapDetectors();

      // Fill the mapped tree entry
      fDataMapper->FillMappedEvent();

      fCurrEvent++;
   }
}

//________________________________________________
void HTRawDataReader::EndProcess()
{
   if (fDataTree)
      delete fDataTree;
   fDataMapper->EndMapping();
   PrintSummary();
}

//________________________________________________
void HTRawDataReader::PrintSummary()
{
   // -- This method print a general final summary of the mapping procedure
   cout << "\n\n--Mapping summary--" << endl;
   printf("Mapping time : %.0f s\n", fTimeElapsed);
   printf("%llu events mapped\n", fCurrEvent);
   printf("--End of Mapping--\n\n");
}
