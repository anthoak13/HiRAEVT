#ifndef HTVETOWALLROOTEVENT_H
#define HTVETOWALLROOTEVENT_H

#include <TROOT.h>

class HTVetoWallData
{
public:

  HTVetoWallData(int);
  virtual ~HTVetoWallData();

  ClassDef(HTVetoWallData,1);
};

class HTVetoWallRootEvent
{
 private:
 int fNumBars;

 public:
 HTVetoWallData fVetoWall;

 HTVetoWallRootEvent(int);
 virtual ~HTVetoWallRootEvent();

 ClassDef(HTVetoWallRootEvent,1);
};

#endif
