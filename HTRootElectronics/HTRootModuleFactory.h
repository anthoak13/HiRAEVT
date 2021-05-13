/* Singelton factory for creating root modules
 *
 * Adam Anthony 5/6/2021
 *
 */
#ifndef HTROOTMODULEFACTORY_H
#define HTROOTMODULEFACTORY_H

#include "TString.h"

#include "HTRootModule.h"

class TTree;

class HTRootModuleFactory {
public:
   static HTRootModuleFactory *Instance();

   /* Create and return a pointer to the new ROOT module. If a tree is passed will set the branch
    * address to the returned pointer. Because of how root manages trees, the pointer to the object
    * might change arbitrarily, but the reference to the pointer will not so we must use the referece
    * to the pointer passed to the TBranch.
    */
   HTRootModule *&CreateRootModule(TString moduleType, TString moduleName, TTree *tr = nullptr);

protected:
   HTRootModuleFactory(){};
   ~HTRootModuleFactory(){};

private:
   static HTRootModuleFactory *_instance;
};

#endif // #ifndef HTROOTMODULEFACTORY_H
