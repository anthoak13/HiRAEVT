#ifndef HTNEUTRONWALLARRAY_H
#define HTNEUTRONWALLARRAY_H

#include <HTNeutronWallBar.h>
#include <TROOT.h>

class HTNeutronWallArray {
private:
   HTNeutronWallBar **fNWArray;
   int fNumBars;

public:
   HTNeutronWallArray(int); // constructor
   ~HTNeutronWallArray();   // destructor

   // Getting methods
   HTNeutronWallBar *GetBar(int) const;
   int GetNumberBars() const;

   void Clear();
};

#endif
