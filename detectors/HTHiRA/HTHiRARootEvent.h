#ifndef HTHIRAROOTEVENT_H
#define HTHIRAROOTEVENT_H

#include <TROOT.h>

class HTHiRAData
{
public:

  HTHiRAData(int);
  virtual ~HTHiRAData();

  ClassDef(HTHiRAData,1);
};

class HTHiRARootEvent
{
 private:
 int fNumTelescopes;

 public:
 HTHiRAData fHiRA;

 HTHiRARootEvent(int);
 virtual ~HTHiRARootEvent();

 ClassDef(HTHiRARootEvent,1);
};

#endif
