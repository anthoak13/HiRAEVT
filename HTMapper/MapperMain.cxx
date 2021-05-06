#include "TString.h"

#include "HTMapper.h"
#include "HiRAEVTLogo.h"

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

void PrintUsage();

// Program to map HiRAEVT data to detectors
// Usage HiRAEVTMapper [configFile] [runNumber]

int main(int argc, char **argv)
{
   // Print program logo
   PrintHiRAEVTMapperLogo();

   if (argc != 3) {
      std::cerr << "HiRAEVTMapper requires three arguments, only " << argc << " passed!" << std::endl;
      PrintUsage();
      return -1;
   }

   // Get the json config file and the run number
   TString configFileName(argv[1]);
   std::ifstream configFile(configFileName);
   Int_t runNumber = TString(argv[2]).Atoi();

   // Check to make sure the passed values are reasonable
   if (runNumber == 0) {
      std::cerr << "ERROR: Invalid run number " << argv[2] << std::endl;
      return -1;
   }
   if (!configFile) {
      std::cerr << "ERROR: Cannot open config file: " << configFileName << std::endl;
      return -1;
   }
   json configData;
   configFile >> configData;

   // Create a new HTMapper object
   // HTMapper *TheMapper = new HTMapper();

   // Pass Argument to HTMapper object and retrieve run number to analyze

   return 0;
}

void PrintUsage()
{
   std::cout << "Usage: " << std::endl << "HiRAEVTMapper [configFile] [runNumber]" << std::endl;
}
