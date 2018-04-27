#ifndef HTMICROBALLROOTEVENT_H
#define HTMICROBALLROOTEVENT_H

#include <TROOT.h>

class HTMicroballData
{
public:

  HTMicroballData();
  virtual ~HTMicroballData();

  ClassDef(HTMicroballData,1);
};

class HTMicroballRootEvent
{
 private:

 public:
 HTMicroballData fMicroball;

 HTMicroballRootEvent();
 virtual ~HTMicroballRootEvent();

 ClassDef(HTMicroballRootEvent,1);
};

#endif
