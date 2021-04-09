#ifndef HTTSTAMPROOTEVENT_H
#define HTTSTAMPROOTEVENT_H

#include <TROOT.h>

#include <stdexcept>



class HTTStampData
{
private:
  const static int MAXNUMDET = 10;

public:
  Int_t fMulti;

  ULong64_t *fTimestamp; //[fMulti]

  HTTStampData(int numDet = MAXNUMDET);

  virtual ~HTTStampData();

  ClassDef(HTTStampData,1);
};

class HTTStampRootEvent
{
 
public:
  HTTStampData fSisTimestamp;
  
  HTTStampRootEvent(int);
  virtual ~HTTStampRootEvent();
  
  ClassDef(HTTStampRootEvent,1);
};

#endif
