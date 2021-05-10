#include "HTMapper.h"

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TTreeReader.h"

#include "HTDetector.h"
#include "HTDetectorMapper.h"
#include "HTMapperFactory.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"
#include "HTRootModuleFactory.h"

#include <time.h>

#include "nlohmann/json.hpp"

HTMapper *HTMapper::fInstance = nullptr;
HTMapper *HTMapper::Instance()
{
   if (fInstance == nullptr)
      fInstance = new HTMapper();
   return fInstance;
}

void HTMapper::Init(json config, Int_t runNumber)
{
   fConfigInfo = config;
   fRunNumber = runNumber;

   std::cout << "*** Opening the input/output files and TTrees ***" << std::endl;
   OpenFiles();
   std::cout << std::endl;

   std::cout << "*** Loading electronic modules from input tree ***" << std::endl;
   // Create all of the electronic modules
   CreateModules();
   std::cout << std::endl;

   std::cout << "*** Initializing detectors and mappers ***" << std::endl;
   // Create all of the detectors
   CreateDetectors();
   std::cout << std::endl;
}

void HTMapper::OpenFiles()
{
   // Open the input file
   TString inputFileName =
      TString::Format("%s/run-%d.root", fConfigInfo["inputDirectory"].get<std::string>().data(), fRunNumber);
   std::cout << "Opening input file: " << inputFileName << std::endl;
   fFileInput = new TFile(inputFileName);
   if (fFileInput->IsZombie())
      throw std::runtime_error("Error opening input file!");

   // Get the input tree
   TString treeName = TString::Format("E%d", fConfigInfo["experimentNumber"].get<int>());
   fTreeInput = (TTree *)fFileInput->Get(treeName);
   if (fTreeInput == nullptr)
      throw std::runtime_error(
         std::string("Could not find tree named ").append(treeName).append(" in ").append(inputFileName));

   // Open the output file
   TString outputFileName =
      TString::Format("%s/mappedRun-%d.root", fConfigInfo["outputDirectory"].get<std::string>().data(), fRunNumber);
   std::cout << "Opening output file: " << outputFileName << std::endl;
   fFileOutput = new TFile(outputFileName, "RECREATE");
   if (fFileInput->IsZombie())
      throw std::runtime_error("Error opening output file!");

   // Create the output tree
   fTreeOutput = new TTree(treeName, treeName);
}

void HTMapper::CreateModules()
{

   // Loop through each module and create a reader of the correct type.
   for (const auto &module : fConfigInfo["modules"]) {
      std::string moduleName = module["moduleName"].get<std::string>();
      std::string moduleType = module["moduleType"].get<std::string>();

      std::cout << "Creating reader for module " << moduleName << " of type " << moduleType << std::endl;

      // Create and register the module
      auto modulePtr = HTRootModuleFactory::Instance()->CreateRootModule(moduleType, moduleName, fTreeInput);
      fModules[moduleName] = modulePtr;
   }
}

void HTMapper::CreateDetectors()
{
   // Loop through each detector and create them
   for (const auto &detector : fConfigInfo["detectors"]) {
      std::string detectorName = detector["detectorName"].get<std::string>();
      std::string detectorType = detector["detectorType"].get<std::string>();
      std::cout << "Creating detector " << detectorName << " of type " << detectorType << std::endl;

      // Create mapper
      fMappers.push_back(HTMapperFactory::Instance()->CreateDetector(detector, fTreeOutput));
   }
}

void HTMapper::MapData()
{
   fTotalEvents = fTreeInput->GetEntries();
   fStartTime = time(nullptr);

   std::cout << "*** Begining loop over " << fTotalEvents << " events ***" << std::endl;

   for (fEventsMapped = 0; fEventsMapped < fTotalEvents; ++fEventsMapped) {
      if (fEventsMapped % 1000 == 0)
         PrintPercentage();

      fTreeInput->GetEntry(fEventsMapped);

      for (const auto &map : fMappers) {
         map->GetDetector()->Clear();
         map->MapAndCalibrate();
      }

      // Fill the tree
      fTreeOutput->Fill();
   }

   // Newline after all of the status printing
   std::cout << std::endl;
}

void HTMapper::End()
{
   fTreeOutput->Write();
   fFileInput->Close();
   fFileOutput->Close();
}

const std::unordered_map<std::string, HTRootModule *> *HTMapper::GetRootModules()
{
   return &fModules;
}

void HTMapper::PrintPercentage()
{
   TDatime now = time(nullptr);
   UInt_t time_elapsed = now.Convert() - fStartTime.Convert();
   Float_t fracDone = (double)fEventsMapped / fTotalEvents;

   std::cout << "Percentage= " << std::fixed << std::setprecision(1) << std::setw(5) << 100 * fracDone << " %   [";

   // Print out status bar
   int numToPrint = 20 * fracDone;
   for (int i = 0; i < 20; ++i)
      if (i < numToPrint)
         std::cout << "=";
      else
         std::cout << " ";
   std::cout << "]   ";

   // Print the elapsed time
   std::cout << "elapsed time: "
             << (time_elapsed < 60 ? time_elapsed : (time_elapsed < 3600 ? time_elapsed / 60 : time_elapsed / 3600))
             << (time_elapsed < 60 ? " s; " : (time_elapsed < 3600 ? " m; " : " h; "));

   if (fEventsMapped > 0) {
      auto remainingEvents = fTotalEvents - fEventsMapped;
      Double_t secondsPerEvent = (Double_t)time_elapsed / fEventsMapped;
      Double_t time_remaining = secondsPerEvent * remainingEvents;

      std::cout << "Estimated remaining time: "
                << (time_remaining < 60 ? time_remaining
                                        : (time_remaining < 3600 ? time_remaining / 60 : time_remaining / 3600))
                << (time_remaining < 60 ? " s      " : (time_remaining < 3600 ? " m      " : " h      "));

   } // End print remaining time
   std::cout << "\r";
   std::cout.flush();
}

Short_t HTMapper::GetAdcEnergy(const std::string &moduleName, int ch)
{
   // Make sure the module exists
   if (fModules.count(moduleName) == 0)
      throw std::invalid_argument(
         std::string("Could not map an energy using module ").append(moduleName).append(" it does not exist."));

   // Get the energy from the module
   auto module = dynamic_cast<HTRootAdc *>(fModules.at(moduleName));
   if (module == nullptr)
      throw std::invalid_argument(std::string("Could not map an energy using module name ")
                                     .append(moduleName)
                                     .append(" it is not of type HTRootAdc."));
   return module->GetData(ch);
}
Double_t HTMapper::GetTimeSingleHit(const std::string &moduleName, int ch)
{
   auto times = GetTimeMultiHit(moduleName, ch);
   return times.size() > 0 ? times.at(0) : -9999;
}
std::vector<Double_t> HTMapper::GetTimeMultiHit(const std::string &moduleName, int ch)
{

   // Make sure the module exists
   if (fModules.count(moduleName) == 0)
      throw std::invalid_argument(
         std::string("Could not map an energy using module ").append(moduleName).append(" it does not exist."));

   // Figure out if we are single or multi hit MCP data
   auto timeModule = fModules.at(moduleName);

   // If this is a multi-hit tdc
   if (timeModule->GetType().EqualTo("HTRootCAEN1x90")) {
      auto multiHit = dynamic_cast<HTRootCAEN1x90 *>(timeModule);
      return *(multiHit->GetData(ch));
   } else if (timeModule->GetType().EqualTo("HTRootCAEN1x90SingleHit")) {
      auto singleHit = dynamic_cast<HTRootCAEN1x90SingleHit *>(timeModule);
      return std::vector<Double_t>{singleHit->GetData(ch)};
   } else
      throw std::invalid_argument(
         std::string("Could not map time using module ").append(moduleName).append(" it is the wrong type."));
}
