#include <HTSisTimestampRootEvent.h>

//________________________________________________
HTSisTimestampData::HTSisTimestampData(int numDetectors) : fMulti(0)
{
   if (numDetectors > MAXNUMDET)
      throw std::invalid_argument(
         TString::Format("Tried to create %d detectors which is larger then the absolute cap of %d", numDetectors,
                         MAXNUMDET)
            .Data());

   fTimestamp = new ULong64_t[numDetectors];
}

//________________________________________________
HTSisTimestampData::~HTSisTimestampData()
{
   delete[] fTimestamp;
}

//________________________________________________
HTSisTimestampRootEvent::HTSisTimestampRootEvent(int num_detectors) : fSisTimestamp(num_detectors) {}

//________________________________________________
HTSisTimestampRootEvent::~HTSisTimestampRootEvent() {}
