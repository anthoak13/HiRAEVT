#ifndef HTVETOWALLARRAY_H
#define HTVETOWALLARRAY_H

#include <TROOT.h>

#include <HTVetoWallBar.h>

class HTVetoWallArray
{
private:
  HTVetoWallBar ** fVWArray;
  int fNumBars;

public:
  HTVetoWallArray(int);                    //constructor
  ~HTVetoWallArray();                      //destructor

  //Getting methods
  HTVetoWallBar * GetBar(Int_t) const;
  Int_t     GetNumberBars() const;

  void Clear();
};

#endif
