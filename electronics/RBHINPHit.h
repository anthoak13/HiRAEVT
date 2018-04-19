#ifndef RBHINPHIT_H
#define RBHINPHIT_H

#include <TROOT.h>

class RBHINPHit
{
public:
  Int_t     fNHits;      // Number of hits
  UShort_t *fXLMIndex;   //[fNHits] // XLM index
  UShort_t *fBank;       //[fNHits] // XLM BANK
  Bool_t   *fChMismatch; //[fNHits] // XLM/FADC ch mismatch
  UShort_t *fChannel;    //[fNHits] // chip channel
  UShort_t *fChip;       //[fNHits] // chip number
  UShort_t *fEnergyHi;   //[fNHits] // raw energy High gain
  UShort_t *fEnergyLo;   //[fNHits] // raw energy Low Gain
  UShort_t *fTime;       //[fNHits] // raw time

  RBHINPHit();
  virtual ~RBHINPHit();

  ClassDef(RBHINPHit,1);
};

#endif
