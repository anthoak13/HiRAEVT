#ifndef HTTSTAMPROOTEVENT_H
#define HTTSTAMPROOTEVENT_H

#include <TROOT.h>

#include <stdexcept>

#define MAXNUMDET 10

class HTTStampData
{
public:
  Int_t fMulti;

  ULong64_t *fTimestamp; //[fMulti]

  HTTStampData(int numDet = MAXNUMDET);

  virtual ~HTTStampData();

  ClassDef(HTTStampData,1);
};

class HTTStampRootEvent
{
private:
  
public:
  HTTStampData fSisTimestamp;
  
  HTTStampRootEvent(int);
  virtual ~HTTStampRootEvent();
  
  ClassDef(HTTStampRootEvent,1);
};

#endif
