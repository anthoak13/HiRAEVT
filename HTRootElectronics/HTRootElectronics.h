#ifndef HTROOTELECTRONICS_H
#define HTROOTELECTRONICS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class HTRootElectronics
{
public :
  HTRootElectronics(const char *);              //!Constructor
  ~HTRootElectronics();                         //!Destructor

  const char * GetName() const;                 //!Returns module name
  virtual void * GetDataPointer() const;        //!Returns the pointer of the fData object

private :
  const char * fName;

};

#endif
