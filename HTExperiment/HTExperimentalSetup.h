#ifndef ____HTExperiment__
#define ____HTExperiment__
//
//  Created by Andrew Rogers on 4/21/14.
//  Modified by Juan Manfredi
//  Modified by Daniele Dell'Aquila (April 2018)
//  Modified by Adam Anthony 4/14/2021
//

// This class is what is written to disk by HiRAEVTUnpacker.
// It contains a vector of electronics modules.

#include "HTExperimentInfo.h"
#include "HTRunInfo.h"
#include "HTUSBStack.h"

#include <HTElectronics.h>
#include <vector>

class HTVmeModule;

class HTExperiment : public TObject {
private:
   std::vector<HTVmeModule *> vmeModules;

public:
   std::vector<HTVmeModule *> *GetVmeModules() { return &vmeModules; }
   void RegisterModule(HTVmeModule *module);

   ClassDef(HTExperiment, 1) // NSCL event-data unpacker.
};

#endif /* defined(____HTExperiment__) */
