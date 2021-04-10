#ifndef HTMICROBALLARRAY_H
#define HTMICROBALLARRAY_H

#include <HTMicroballRing.h>
#include <MicroballConstants.h>
#include <TROOT.h>

class HTMicroballArray {
private:
   HTMicroballRing **fMicroballRing;

public:
   HTMicroballArray();
   ~HTMicroballArray();

   HTMicroballRing *GetRing(int) const;
   int GetNumberRings() const;

   void Clear();
};

#endif
