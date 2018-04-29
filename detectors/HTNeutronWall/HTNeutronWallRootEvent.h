#ifndef HTNEUTRONWALLROOTEVENT_H
#define HTNEUTRONWALLROOTEVENT_H

#include <TROOT.h>

class HTNeutronWallData
{
public:

  HTNeutronWallData(int);
  virtual ~HTNeutronWallData();

  ClassDef(HTNeutronWallData,1);
};

class HTNeutronWallRootEvent
{
 private:
 int fNumBars;

 public:
 HTNeutronWallData fNeutronWall;

 HTNeutronWallRootEvent(int);
 virtual ~HTNeutronWallRootEvent();

 ClassDef(HTNeutronWallRootEvent,1);
};

#endif
