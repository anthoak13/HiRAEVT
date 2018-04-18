#ifndef RBDAQSTACKINFO_H
#define RBDAQSTACKINFO_H

#include <vector>
#include <string>

#include <RBElectronics.h>
#include <RBModuleInfo.h>

class RBDAQStackInfo
{
public:
  RBDAQStackInfo(const char * name, int stackID);
  ~RBDAQStackInfo();

  void Clear();

  int GetNModules() const;                     //! Returns the number of modules in the stack
  int GetStackID() const;                      //! Returns the ID of the stack
  const char * GetStackName() const;           //! Returns the name of the stack
  RBElectronics * GetModule(int) const;        //! Returns the pointer of the i-th module
  const char * GetModuleType(int) const;       //! Returns a const char * indicating module type
  int GetModuleVSN(int) const;                 //! Returns the VSN of the i-th module
  RBModuleInfo  * GetModuleInfo(int) const;    //! Returns the pointer of the i-th module RBModuleInfo class

  void AddModuleInfo(RBModuleInfo *);          //! Add a new module to the stack info class

private:
  int fNModules;                                //! Number of modules in stack
  std::string fStackName;                       //! Name of the stack
  int fStackID;                                 //! ID of the stack
  std::vector <RBModuleInfo *> fModuleInStack;  //! RBModuleInfo objects

};

#endif
