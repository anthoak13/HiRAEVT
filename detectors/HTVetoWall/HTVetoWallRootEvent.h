#ifndef HTVETOWALLROOTEVENT_H
#define HTVETOWALLROOTEVENT_H

#include <TROOT.h>

class HTVetoWallData
{
public:

  HTVetoWallData();
  virtual ~HTVetoWallData();

  ClassDef(HTVetoWallData,1);
};

class HTVetoWallRootEvent
{
 private:

 public:
 HTVetoWallData fVetoWall;

 HTVetoWallRootEvent();
 virtual ~HTVetoWallRootEvent();

 ClassDef(HTVetoWallRootEvent,1);
};

#endif
