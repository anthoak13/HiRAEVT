#include <HTTStampRootEvent.h>

//________________________________________________
HTTStampData::HTTStampData(int numDetectors) : fMulti(0)
{
  if(numDetectors > MAXNUMDET)
    throw std::invalid_argument(TString::Format(
				  "Tried to create %d detectors which is larger then the absolute cap of %d",
				  numDetectors, MAXNUMDET).Data());

  fTimestamp = new ULong64_t[numDetectors];
}

//________________________________________________
HTTStampData::~HTTStampData()
{
  delete [] fTimestamp;
}

//________________________________________________
HTTStampRootEvent::HTTStampRootEvent(int num_detectors) :
  fSisTimestamp(num_detectors)
{}

//________________________________________________
HTTStampRootEvent::~HTTStampRootEvent()
{}
