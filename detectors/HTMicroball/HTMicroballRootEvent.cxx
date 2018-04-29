#include <HTMicroballRootEvent.h>

/* WARNING: uBall number of rings and detectors per ring is fixed */
const int N_RINGS = 9;
const int N_DETS[] = {6, 10, 12, 12, 14, 14, 12, 10, 6};
// Detector numbering within a ring starts from 1 but the arrays start from 0
/******************************************************************/

//________________________________________________
HTMicroballData::HTMicroballData()
{}

//________________________________________________
HTMicroballData::~HTMicroballData()
{}

//________________________________________________
HTMicroballRootEvent::HTMicroballRootEvent()
{}

//________________________________________________
HTMicroballRootEvent::~HTMicroballRootEvent()
{}
