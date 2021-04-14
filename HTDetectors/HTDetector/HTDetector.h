#ifndef HTDETECTOR_H
#define HTDETECTOR_H

// This is the abstract base class for all detectors. It is responsible for saving the state of
// the detector. Taking the raw data from the unpacker and filling the member variables is the
// responsibility of the Detector Map class. This class has no direct knowledge of the detector
// map class.

#include "TString.h"

class HTDetector {
public:

   HTDetector(const TString detectorName); //Constructor
   virtual ~HTDetector();                  // Destructor

   virtual void Clear() =0; // Clear detector data to -9999

   const TString GetName() const { return fName; } // Returns detector name
   const TString GetType() const { return fType; } // Returns detector type

protected:
   std::string fName; // Detector Name
   std::string fType; // Detector Type

   ClassDef(HTDetector, 1)
};

#endif
