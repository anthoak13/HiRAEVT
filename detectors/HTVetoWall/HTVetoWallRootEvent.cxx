#include <HTVetoWallRootEvent.h>

//________________________________________________
HTVetoWallData::HTVetoWallData(int num_bars)
{}

//________________________________________________
HTVetoWallData::~HTVetoWallData()
{}

//________________________________________________
HTVetoWallRootEvent::HTVetoWallRootEvent(int num_bars) :
fNumBars(num_bars),
fVetoWall(fNumBars)
{}

//________________________________________________
HTVetoWallRootEvent::~HTVetoWallRootEvent()
{}
