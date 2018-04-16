#ifndef RBDAQSTACKINFO_H
#define RBDAQSTACKINFO_H

#include <vector>

#include <RBElectronics.h>
#include <RBModuleInfo.h>

class RBDAQStackInfo
{
public:
  RBDAQStackInfo();
  ~RBDAQStackInfo();
  
  void Clear();

  int GetNModules() const;                     //! Returns the number of modules in the stack
  RBElectronics * GetModule(int) const;        //! Returns the pointer of the i-th module
  const char * GetModuleType(int) const;       //! Returns a const char * indicating module type
  int GetModuleVSN(int) const;                 //! Returns the VSN of the i-th module
  RBModuleInfo  * GetModuleInfo(int) const;    //! Returns the pointer of the i-th module RBModuleInfo class

  void AddModule(RBElectronics *);             //! Add a new module to the stack info class

private:
  int fNModules;                                //! Number of modules in stack 
  std::vector <RBModuleInfo *> fModuleInStack;  //! RBModuleInfo objects

};

#endif
