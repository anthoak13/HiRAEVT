#ifndef HTNEUTRONWALLARRAY_H
#define HTNEUTRONWALLARRAY_H

#include <TROOT.h>

#include <HTNeutronWallBar.h>

class HTNeutronWallArray
{
private:
  HTNeutronWallBar ** fNWArray;
  int fNumBars;

public:
  HTNeutronWallArray(int);             //constructor
  ~HTNeutronWallArray();               //destructor

  //Getting methods
  HTNeutronWallBar * GetBar(int) const;
  int       GetNumberBars() const;

  void Clear();
};

#endif
