
#include "TFile.h"

#include "HTModuleUnpacker.h"
#include "HTUnpacker.h"
#include "HTExperimentInfo.h"
#include "HTFilter.h"
#include "HiRAEVTLogo.h"

#include <CFatalException.h>
#include <CFilterMain.h>

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

char **SetMainArgs(json config, Int_t runNumber, int &argc, char *agrv[]);
TFile *GetOutFile(json config, Int_t runNumber);
void PrintUsage();

/// The main function
/**! main function
  Creates a CFilterMain object and
  executes its operator()() method.

  Takes 2 arguments, first is the config file descibing the experiment
  the second is the run number to unpack.

  \return 0 for normal exit,
          1 for known fatal error,
          2 for unknown fatal error
*/
int main(int argc, char *argv[])
{
   PrintHiRAEVTUnpackerLogo();

   int status = 0;

   // Check for proper numbner of command line inputs
   if (argc != 3) {
      std::cerr << "HiRAEVTUnpacker requires three arguments, only " << argc << " passed!" << std::endl;
      PrintUsage();
      return -1;
   }

   TString configFileName(argv[1]);           // Get config file name
   Int_t runNumber = TString(argv[2]).Atoi(); // Get run number

   // Open the configFile and load in the json data
   std::ifstream confFile(configFileName);
   if (!confFile) {
      std::cerr << "ERROR: Could not open config file: " << configFileName << std::endl;
      return -1;
   }
   json configData;
   confFile >> configData;

   // Create the main app
   char **mainArgs = SetMainArgs(configData, runNumber, argc, argv);
   CFilterMain theApp(argc, mainArgs);
   std::cout << "**Main app created**" << std::endl;

   // Create and register our filter (what actually unpacks the data)
   HTUnpacker *unpacker = new HTUnpacker(configData, runNumber);
   HTFilter filter(unpacker);
   std::cout << "** Unpacker filter intialized**" << std::endl;
   theApp.registerFilter(&filter);
   std::cout << "** Unpacker filter registered**" << std::endl;

   // Run the main loop (unpack the data with repeated calls to HTFilter::operator()
   theApp();
   unpacker->PrintSummary();

   /* std::cout << "Finished unpacking, saving tree" << std::endl;
   TFile *outFile = GetOutFile(configData, runNumber);
   if (outFile != nullptr && outFile->IsOpen())
      unpacker->GetExperimentInfo()->Write();
   else
      std::cout << "Didn't wreite";
   outFile->Close();
   std::cout << "Finished saving tree" << std::endl;
   */
   return status;
}

void PrintUsage()
{
   std::cout << "Usage: " << std::endl << "HiRAEVTUnpacker [configFile] [runNumber]" << std::endl;
}

char **SetMainArgs(json configData, Int_t runNumber, int &argc, char *argv[])
{

   // Set the source
   TString *source = new TString();
   if (configData["evtDirectory"].is_string())
      source->Form("--source=file://%s/run%d/run-%04d-00.evt", configData["evtDirectory"].get<std::string>().c_str(),
                   runNumber, runNumber);
   else
      throw std::runtime_error("The value with key \"evtDirectory\" is not a string");

   // Set the sink
   TString *sink = new TString("--sink=file:///dev/null");

   argc = 3;
   char **newArgs = new char *[argc];
   newArgs[0] = argv[0];
   newArgs[1] = const_cast<char *>(source->Data());
   newArgs[2] = const_cast<char *>(sink->Data());
   return newArgs;
}

TFile *GetOutFile(json configData, Int_t runNumber)
{
   // Set the output file from the config file
   TString outFileName;
   if (configData["outputDirectory"].is_string())
      outFileName =
         TString::Format("%s/run-%d.root", configData["outputDirectory"].get<std::string>().c_str(), runNumber);
   else {
      std::cerr << "ERROR: input badly formated, the key-value pair \"outputDirectory\":"
                << configData["outputDirectory"] << " is not a string!" << std::endl;
      return nullptr;
   }

   // Open the output file
   return new TFile(outFileName, "RECREATE");
}
