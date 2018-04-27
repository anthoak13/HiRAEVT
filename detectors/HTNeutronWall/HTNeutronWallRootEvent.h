#ifndef HTNEUTRONWALLROOTEVENT_H
#define HTNEUTRONWALLROOTEVENT_H

#include <TROOT.h>

class HTNeutronWallData
{
public:

  HTNeutronWallData();
  virtual ~HTNeutronWallData();

  ClassDef(HTNeutronWallData,1);
};

class HTNeutronWallRootEvent
{
 private:

 public:
 HTNeutronWallData fNeutronWall;

 HTNeutronWallRootEvent();
 virtual ~HTNeutronWallRootEvent();

 ClassDef(HTNeutronWallRootEvent,1);
};

#endif
