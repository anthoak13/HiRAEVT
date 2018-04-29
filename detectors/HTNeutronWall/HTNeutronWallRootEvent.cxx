#include <HTNeutronWallRootEvent.h>

//________________________________________________
HTNeutronWallData::HTNeutronWallData(int num_bars)
{}

//________________________________________________
HTNeutronWallData::~HTNeutronWallData()
{}

//________________________________________________
HTNeutronWallRootEvent::HTNeutronWallRootEvent(int num_bars) :
fNumBars(num_bars),
fNeutronWall(fNumBars)
{}

//________________________________________________
HTNeutronWallRootEvent::~HTNeutronWallRootEvent()
{}
