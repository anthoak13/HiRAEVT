#ifndef HTROOTELECTRONICS_H
#define HTROOTELECTRONICS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class HTRootElectronics
{
public :
  HTRootElectronics();                          //!Constructor
  ~HTRootElectronics();                         //!Destructor

  virtual void * GetDataPointer() const;        //!Returns the pointer of the fData object

private :

};

#endif
