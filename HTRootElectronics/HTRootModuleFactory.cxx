#include "HTRootModuleFactory.h"

#include "TTree.h"

#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"
#include "HTRootModule.h"
#include "HTRootSisTimestamp.h"

HTRootModuleFactory *HTRootModuleFactory::_instance = nullptr;

HTRootModuleFactory *HTRootModuleFactory::Instance()
{
   if (_instance == nullptr) {
      _instance = new HTRootModuleFactory();
   }

   return _instance;
}

//
HTRootModule *&HTRootModuleFactory::CreateRootModule(TString moduleType, TString moduleName, TTree *tr)
{
   // Dynamically allocated a pointer to the pointer for SetBranchAddress
   // If this isn't on done, then the pointer to pointer passed is deleted when it goes out
   // of scope at the end of the funtion, leaving undefined behavior.

   HTRootModule **module = new HTRootModule *;
   *module = nullptr;

   if (moduleType.EqualTo("HTRootAdc"))
      *module = new HTRootAdc(moduleName);
   if (moduleType.EqualTo("HTRootCAEN1x90"))
      *module = new HTRootCAEN1x90(moduleName);
   if (moduleType.EqualTo("HTRootCAEN1x90SingleHit"))
      *module = new HTRootCAEN1x90SingleHit(moduleName);
   if (moduleType.EqualTo("HTRootSisTimestamp"))
      *module = new HTRootSisTimestamp(moduleName);

   // Make sure the module type is defined
   if (*module == nullptr)
      throw std::invalid_argument(
         std::string("Failed to create module type ").append(moduleType).append(" is not defined!"));

   // If a tree was passed, set the branch address
   if (tr != nullptr)
      tr->SetBranchAddress(moduleName, module);
   return *module;
}
