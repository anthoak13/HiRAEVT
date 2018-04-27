#ifndef HTFORWARDARRAYROOTEVENT_H
#define HTFORWARDARRAYROOTEVENT_H

#include <TROOT.h>

class HTForwardArrayData
{
public:

  HTForwardArrayData();
  virtual ~HTForwardArrayData();

  ClassDef(HTForwardArrayData,1);
};

class HTForwardArrayRootEvent
{
 private:

 public:
 HTForwardArrayData fForwardArray;

 HTForwardArrayRootEvent();
 virtual ~HTForwardArrayRootEvent();

 ClassDef(HTForwardArrayRootEvent,1);
};

#endif
