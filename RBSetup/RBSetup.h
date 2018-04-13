#ifndef ____RBSetup__
#define ____RBSetup__

#include <stdio.h>

#include <TNamed.h>
#include <RBShared.h>
#include <RBExperiment.h>

class RBSetup : public TNamed
{
private:

public:
  RBSetup();
  ~RBSetup();

  void Print(){};

  ClassDef(RBSetup,1);
};


#endif /* defined(____RBSetup__) */
