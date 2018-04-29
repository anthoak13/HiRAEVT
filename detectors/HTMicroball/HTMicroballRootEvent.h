#ifndef HTMICROBALLROOTEVENT_H
#define HTMICROBALLROOTEVENT_H

#include <TROOT.h>

class HTMicroballData
{
public:
  Int_t    fmulti;
  Int_t    *fnumring;     //[fmulti]
  Int_t    *fnumdet;      //[fmulti]
  Short_t  *fTail;        //[fmulti]
  Short_t  *fE;           //[fmulti]
  Short_t  *fTime;        //[fmulti]

  HTMicroballData(int);
  virtual ~HTMicroballData();

  ClassDef(HTMicroballData,1);
};

class HTMicroballRootEvent
{
 private:
 int fNumDetectors;

 public:
 HTMicroballData fMicroball;

 HTMicroballRootEvent(int);
 virtual ~HTMicroballRootEvent();

 ClassDef(HTMicroballRootEvent,1);
};

#endif
