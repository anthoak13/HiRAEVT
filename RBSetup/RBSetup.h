#ifndef ____RBSetup__
#define ____RBSetup__

#include <stdio.h>

#include <TNamed.h>

#include <RBExperiment.h>

class RBSetup : public TNamed
{
private:
  RBExperiment *fExperiment;
  
public:
  RBSetup();
  ~RBSetup();
  
  RBExperiment* GetInitializedExp(){ return fExperiment;}
  void Print(){};
 
  ClassDef(RBSetup,1);
};


#endif /* defined(____RBSetup__) */
