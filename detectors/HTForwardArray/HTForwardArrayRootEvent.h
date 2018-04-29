#ifndef HTFORWARDARRAYROOTEVENT_H
#define HTFORWARDARRAYROOTEVENT_H

#include <TROOT.h>

class HTForwardArrayData
{
public:

  HTForwardArrayData(int);
  virtual ~HTForwardArrayData();

  ClassDef(HTForwardArrayData,1);
};

class HTForwardArrayRootEvent
{
 private:
 int fNumDetectors;

 public:
 HTForwardArrayData fForwardArray;

 HTForwardArrayRootEvent(int);
 virtual ~HTForwardArrayRootEvent();

 ClassDef(HTForwardArrayRootEvent,1);
};

#endif
