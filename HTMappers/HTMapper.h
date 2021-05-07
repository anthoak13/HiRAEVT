#ifndef HTMAPPER_H
#define HTMAPPER_H

// This is a singleton that manages the mapper.
// It loads the passed config file, sets up the input and output ROOT files and registers the trees
// It also provides read-only access to all of the input modules.

#include "TString.h"

#include "Rtypes.h"

#include <iostream>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// Forward declerations
class TFile;
class TTree;
class HTRootModule;
class TTreeReader;

class HTMapper {

private:
   static HTMapper *fInstance;
   TTree *fTreeOutput; // TTree with mapped data
   TFile *fFileOutput; // TFile with output tree
   TTree *fTreeInput;
   TFile *fFileInput; // TFile with input tree

   int fRunNumber; //! Run number to analyze
   json fConfigInfo;

   // List of all modules in tree
   std::unordered_map<std::string, HTRootModule *> fModules; // fModules[moduleName] = module

   void CreateModules();
   void CreateDetectors();

protected:
   HTMapper();  // Constructor
   ~HTMapper(); //! Destructor

public:
   static HTMapper *Instance();
   void Init(json config, Int_t runNumber);

   // Getters
   TTree *GetInputTree() const;  //! Returns a pointer to the TTree containing data to map
   TTree *GetOutputTree() const; //! Returns a pointer to the TTree containing mapped data

   // Returns pointer to the map of root modules
   const std::unordered_map<std::string, HTRootModule *> *GetRootModules();

   // Setters

   //
   void MapData(); // Loops through input tree and maps data
};

#endif
