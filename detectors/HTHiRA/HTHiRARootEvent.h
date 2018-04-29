#ifndef HTHIRAROOTEVENT_H
#define HTHIRAROOTEVENT_H

#include <TROOT.h>

class HTHiRAStrip
{
public:
  Int_t    fmulti;
  Int_t    *fnumstrip;   //[fmulti]
  UShort_t *fEnergyHi;   //[fmulti]
  UShort_t *fEnergyLo;   //[fmulti]
  UShort_t *fTime;       //[fmulti]

  HTHiRAStrip();
  virtual ~HTHiRAStrip();

  ClassDef(HTHiRAStrip,1);
};

class HTHiRACsI
{
public:
  Int_t    fmulti;
  Int_t    *fnumcsi;     //[fmulti]
  UShort_t *fEnergy;     //[fmulti]
  Double_t *fTime;       //[fmulti]

  HTHiRACsI();
  virtual ~HTHiRACsI();

  ClassDef(HTHiRACsI,1);
};

class HTHiRAData
{
public:
  HTHiRAStrip fDE;
  HTHiRAStrip fEF;
  HTHiRAStrip fEB;
  HTHiRACsI   fCsI;

  HTHiRAData();
  virtual ~HTHiRAData();

  ClassDef(HTHiRAData,1);
};

class HTHiRARootEvent
{
 private:
 int fNumTelescopes;

 public:
 HTHiRAData *fHiRA;

 HTHiRARootEvent(int);
 virtual ~HTHiRARootEvent();

 ClassDef(HTHiRARootEvent,1);
};

#endif
