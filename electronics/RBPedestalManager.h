#ifndef __RBPEDESTALMANAGER_H
#define __RBPEDESTALMANAGER_H

#include <TROOT.h>
#include <TString.h>

class RBPedestalManager
{
private:
  Int_t   *fPedestals;
  
  Bool_t  fPedSet;
  
public:
  RBPedestalManager(Int_t);
  RBPedestalManager(const char *, Int_t);
  ~RBPedestalManager();
  
  // Loading methods
  Int_t LoadPedestals(const char *);
  
  // Getting methods
  Int_t  GetPedestalValue(Int_t) const;
  Bool_t IsSet() const;
};

#endif