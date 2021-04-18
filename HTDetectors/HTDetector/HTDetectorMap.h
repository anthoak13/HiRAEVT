#ifndef HTDETECTORMAP_H
#define HTDETECTORMAP_H

// This is the abstract base class for all detectors mappers. It is responsible for parsing its
// detecors part of the mapping file, and filling the detector with the correct data on each event
// If a calibration file is defined in the mapping class, it is responsible for ensuring that the
// calibration class gets called. This class is never written to disk, so doesn't get a streamer
// no linkdef or ClassDef

#include "TString.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class HTDetectorMap {
public:
   HTDetectorMap(json mappingJSON); // Constructor
   virtual ~HTDetectorMap() = 0;    // Destructor

protected:
   TString fName;
};

#endif
