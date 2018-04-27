#ifndef HTHIRAROOTEVENT_H
#define HTHIRAROOTEVENT_H

#include <TROOT.h>

class HTHiRAData
{
public:

  HTHiRAData();
  virtual ~HTHiRAData();

  ClassDef(HTHiRAData,1);
};

class HTHiRARootEvent
{
 private:

 public:
 HTHiRAData fNeutronWall;

 HTHiRARootEvent();
 virtual ~HTHiRARootEvent();

 ClassDef(HTHiRARootEvent,1);
};

#endif
