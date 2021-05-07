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
class HTMapper;

class HTDetectorMapper : public TObject {
protected:
   HTDetector *fDetector;         // Owned by the mapper object, the detector this is filling
   const HTMapper *fParentMapper; // A pointer to the object that owns this mapper

public:
   virtual ~HTDetectorMapper() {} // virtual so the derived destructor is always called

   virtual void Map() = 0; // Called at each event.
   HTDetector *GetDetector() { return fDetector; }
};

#endif //#define HTDETECTORMAPPER_H
