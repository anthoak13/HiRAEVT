#ifndef HTHIRACSI_H
#define HTHIRACSI_H

#include <TROOT.h>

class HTHiRACsI
{
public :
  HTHiRACsI();
  ~HTHiRACsI();

  void Clear();

  Short_t GetEnergy() const;
  Double_t GetTime() const;

  void SetEnergy(Short_t);
  void SetTime(Double_t);

private :
  Short_t fEnergy;
  Double_t fTime;

};

#endif
