#ifndef HTIONCHAMBERROOTEVENT_H
#define HTIONCHAMBERROOTEVENT_H


#include <TROOT.h>

class HTIonChamberData
{
public:
  Int_t    fmulti;
  Int_t    *fnumdet;      //[fmulti]
  Short_t  *fE;           //[fmulti]
  Double_t *fTime;        //[fmulti]

  HTIonChamberData(int);
  virtual ~HTIonChamberData();

  ClassDef(HTIonChamberData,1);
};

class HTIonChamberRootEvent
{

 public:
 HTIonChamberData fIonChamber;

 HTIonChamberRootEvent(int);
 virtual ~HTIonChamberRootEvent();

 ClassDef(HTIonChamberRootEvent,1);
};

#endif
