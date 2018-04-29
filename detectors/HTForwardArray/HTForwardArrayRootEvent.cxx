#include <HTForwardArrayRootEvent.h>

//________________________________________________
HTForwardArrayData::HTForwardArrayData(int num_detectors)
{}

//________________________________________________
HTForwardArrayData::~HTForwardArrayData()
{}

//________________________________________________
HTForwardArrayRootEvent::HTForwardArrayRootEvent(int num_detectors) :
fNumDetectors(num_detectors),
fForwardArray(fNumDetectors)
{}

//________________________________________________
HTForwardArrayRootEvent::~HTForwardArrayRootEvent()
{}
