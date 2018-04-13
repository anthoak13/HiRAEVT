#ifndef RBDAQSTACKINFO_H
#define RBDAQSTACKINFO_H

#include <vector>

#include <RBElectronics.h>

class RBDAQStackInfo
{
public:
  RBDAQStackInfo();
  ~RBDAQStackInfo();

  int GetNModules();                  //! Returns the number of modules in the stack
//  RBElectronics * GetModule(int);     //! Returns the pointer of the i-th module
  int GetModuleVSN(int);              //! Returns the VSN of the i-th module

//  void AddModule(RBElectronics *);    //! Add a new module to the stack info class

private:
//  std::vector <RBElectronics *> fModuleInStack

};

#endif
