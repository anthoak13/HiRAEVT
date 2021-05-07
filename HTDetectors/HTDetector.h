#ifndef HTDETECTOR_H
#define HTDETECTOR_H

// This is the abstract base class for all detectors. It is responsible for saving the state of
// the detector. Taking the raw data from the unpacker and filling the member variables is the
// responsibility of the Detector Map class. This class has no direct knowledge of the detector
// map class.

#include "TObject.h"
#include "TString.h"

#include "Rtypes.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class HTDetector : public TObject {
protected:
   TString fName; // Detector Name
   TString fType; // Detector Type

public:
   HTDetector(const TString detectorName); // Constructor
   virtual ~HTDetector();                  // Destructor

   virtual void Clear() = 0; // Clear detector data to -9999

   // Fill the calibrated detector parameters using the filled raw data and
   // the passed calibration JSON file fragment
   virtual void Calibrate(const json &calibration) = 0;

   const char *GetName() const override { return fName.Data(); } // Returns detector name
   const TString GetType() const { return fType; }               // Returns detector type

   ClassDefOverride(HTDetector, 2)
};

#endif
