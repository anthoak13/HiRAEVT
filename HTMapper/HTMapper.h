#ifndef HTMAPPER_H
#define HTMAPPER_H

// This class manages the mapper. It loads the passed config file, sets up the input and output ROOT files.

#include "Rtypes.h"

#include <iostream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// Forward declerations
class TFile;
class TTree;

class HTMapper {

private:
   TTree *fTreeOutput; // TTree with mapped data
   TFile *fFileOutput; // TFile with output tree
   TTree *fTreeInput;  // TTree with input raw data
   TFile *fFileInput;  // TFile with input tree

   int fRunNumber;     //! Run number to analyze
   json fConfigInfo;

public:
   HTMapper(json config, Int_t runNumber); // Constructor
   ~HTMapper();                            //! Destructor

   // Getters
   TTree *GetInputTree() const;  //! Returns a pointer to the TTree containing data to map
   TTree *GetOutputTree() const; //! Returns a pointer to the TTree containing mapped data

   // Setters

   //
   void MapData(); // Loops through input tree and maps data
};

#endif
