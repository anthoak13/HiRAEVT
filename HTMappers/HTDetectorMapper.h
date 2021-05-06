#ifndef HTDETECTORMAPPER_H
#define HTDETECTORMAPPER_H

// This is the interface for a mapper. A mapper is created for each detector and holds a pointer to the detector class
// getting filled. On each event, after the pointers to the root modules have been updated, the function Map() is called
// on each mapper.

#include "TObject.h"
#include "TString.h"

#include <map>

class HTDetector;
class HTRootModule;

class HTDetectorMapper : public TObject {
private:
   HTDetector *fDetector;
   std::map<TString, HTRootModule *> fModules;

public:
   virtual void Map() = 0; // Called at each event.
};

#endif //#define HTDETECTORMAPPER_H
