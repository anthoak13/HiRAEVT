#ifndef ____HTExperiment__
#define ____HTExperiment__
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//  Modified by Daniele Dell'Aquila (April 2018)
//  Modified by Adam Anthony 4/14/2021
//

// This class contains a vector of electronics modules. These modules are what are
// written to disk by HiRAEVTUnpacker.

#include "TObject.h"
#include "TString.h"

#include <vector>

class HTRootModule;

class HTExperiment : public TObject {
private:
   TString fName;
   std::vector<HTRootModule *> fRootModules;

public:
   HTExperiment(); // Default constuctor for IO
   HTExperiment(Int_t experimentNumber);

   std::vector<HTRootModule *> *GetModules() { return &fRootModules; }
   void RegisterModule(HTRootModule *module) { fRootModules.emplace_back(module); }

   virtual const char *GetName() const override { return fName.Data(); }
   ClassDefOverride(HTExperiment, 1) // NSCL event-data unpacker.
};

#endif /* defined(____HTExperiment__) */
