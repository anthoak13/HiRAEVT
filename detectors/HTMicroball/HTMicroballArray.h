#ifndef HTMICROBALLARRAY_H
#define HTMICROBALLARRAY_H

#include <TROOT.h>

#include <HTMicroballRing.h>

class HTMicroballArray
{
private:
  HTMicroballRing ** fMicroballRing;

public:
  HTMicroballArray();
  ~HTMicroballArray();

  HTMicroballRing * GetRing(int) const;
  int GetNumberRings() const;

  void Clear();



};

#endif
