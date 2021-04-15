
#include <CFatalException.h>
#include <CFilterMain.h>
#include <HTFilter.h>
#include <HiRAEVTLogo.h>
#include <Unpacker.h>
#include <iostream>
#include <fstream>

#include "TFile.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

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

   //Check for proper numbner of command line inputs
   if(argc != 3)
   {
      std::cerr << "HiRAEVTUnpacker requires three arguments, only "
		<< argc << " passed!" << std::endl;
      PrintUsage();
   }
   
   
   TString configFileName(argv[1]); //Get config file name
   Int_t runNumber = TString(argv[2]).Atoi(); //Get run number

   //Open the configFile and load in the json data
   ifstream confFile(configFileName);
   if(!confFile)
   {
      std::cerr << "ERROR: Could not open config file: " << configFileName << std::endl;
      return -1;
   }
   json configData;
   confFile >> configData;
   
   // Set the source parameter from the config file
   TString source;
   if(configData["evtDirectory"].is_string())
      source = TString::Format("--source=file://%s/run%d/run-%04d-00.evt",
			       configData["evtDirectory"].get<std::string>().c_str(),
			       runNumber, runNumber);
   else
   {
      std::cerr << "ERROR: input badly formated, the key-value pair \"evtDirectory\":"
		<< configData["evtDirectory"] << " is not a string!" << std::endl;
      return -1;
   }

   // Set the output file from the config file
   TString outFileName;
   if(configData["outputDirectory"].is_string())
      outFileName = TString::Format("%s/run-%d.root",
			       configData["outputDirectory"].get<std::string>().c_str(),
			       runNumber);
   else
   {
      std::cerr << "ERROR: input badly formated, the key-value pair \"outputDirectory\":"
		<< configData["outputDirectory"] << " is not a string!" << std::endl;
      return -1;
   }
   TString sink("--sink=file:///dev/null");

   //Open the output file
   TFile *outFile = new TFile(outFileName, "RECREATE");
   if(!outFile->IsOpen()) {
      std::cerr << "ERROR: Failed to open output file: " << outFileName << std::endl;
      return -1;
   }
   

   //Create the main app
   char *newArgs[3];
   newArgs[0] = argv[0];
   newArgs[1] = const_cast<char*>(source.Data());
   newArgs[2] = const_cast<char*>(sink.Data());
   CFilterMain theApp(3, newArgs);

   std::cout << "**Main app created**" << std::endl;

   HTFilter filter(configData);
   
   std::cout << "** Unpacker filter intialized**" << std::endl;

   theApp.registerFilter(&filter);
   std::cout << "** Unpacker filter registered**" << std::endl;

   // Run the main loop
   theApp();

   std::cout << "Finished unpacking, saving tree" << std::endl;

   if(outFile->IsOpen())
      filter.GetExperimentInfo()->Write();
   else
      cout << "Didn't wreite";
   outFile->Close();
   std::cout << "Finished saving tree" << std::endl;
   return status;
}

void PrintUsage()
{
   std::cout << "Usage: " << std::endl
	     << "HiRAEVTUnpacker [configFile] [runNumber]" << std::endl;
}
