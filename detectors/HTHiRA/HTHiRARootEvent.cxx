#include <HTHiRARootEvent.h>

//________________________________________________
HTHiRAData::HTHiRAData(int num_telescopes)
{}

//________________________________________________
HTHiRAData::~HTHiRAData()
{}

//________________________________________________
HTHiRARootEvent::HTHiRARootEvent(int num_telescopes) :
fNumTelescopes(num_telescopes),
fHiRA(fNumTelescopes)
{}

//________________________________________________
HTHiRARootEvent::~HTHiRARootEvent()
{}
