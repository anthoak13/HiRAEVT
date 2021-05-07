#include "HTUnpackerFactory.h"

#include "TTree.h"

#include "HTCAEN1x90Unpacker.h"
#include "HTCAEN7xxUnpacker.h"
#include "HTMADC32Unpacker.h"
#include "HTRootAdc.h"
#include "HTRootCAEN1x90.h"
#include "HTRootCAEN1x90SingleHit.h"
#include "HTRootSisTimestamp.h"
#include "HTSisTimestampUnpacker.h"

#include <iostream>

HTUnpackerFactory *HTUnpackerFactory::_instance = nullptr;

HTUnpackerFactory::HTUnpackerFactory() {}

HTUnpackerFactory::~HTUnpackerFactory() {}

HTUnpackerFactory *HTUnpackerFactory::Instance()
{
   if (_instance == nullptr) {
      _instance = new HTUnpackerFactory();
   }

   return _instance;
}

HTModuleUnpacker *HTUnpackerFactory::CreateUnpacker(json moduleDescription, TTree *tr)
{
   TString unpackerType = moduleDescription["moduleType"].get<std::string>();

   HTModuleUnpacker *unpacker = nullptr;

   if (unpackerType.EqualTo("HTSisTimestampUnpacker")) {
      unpacker = new HTSisTimestampUnpacker(moduleDescription);
      if (tr != nullptr)
         tr->Branch(unpacker->GetRootModule()->GetName(), (HTRootSisTimestamp *)unpacker->GetRootModule(), 32000, 1);
   }

   if (unpackerType.EqualTo("HTCAEN1x90Unpacker")) {
      unpacker = new HTCAEN1x90Unpacker(moduleDescription);

      if (tr != nullptr) {

         if (dynamic_cast<HTCAEN1x90Unpacker *>(unpacker)->IsSingleHit())
            tr->Branch(unpacker->GetRootModule()->GetName(), (HTRootCAEN1x90SingleHit *)unpacker->GetRootModule(),
                       32000, 1);
         else
            tr->Branch(unpacker->GetRootModule()->GetName(), (HTRootCAEN1x90 *)unpacker->GetRootModule(), 32000, 1);
      }
   }
   if (unpackerType.EqualTo("HTCAEN7xxUnpacker")) {
      unpacker = new HTCAEN7xxUnpacker(moduleDescription);
      if (tr != nullptr)
         tr->Branch(unpacker->GetRootModule()->GetName(), (HTRootAdc *)unpacker->GetRootModule(), 32000, 1);
   }

   if (unpackerType.EqualTo("HTMADC32Unpacker")) {
      unpacker = new HTMADC32Unpacker(moduleDescription);
      if (tr != nullptr)
         tr->Branch(unpacker->GetRootModule()->GetName(), (HTRootAdc *)unpacker->GetRootModule(), 32000, 1);
   }

   return unpacker;
}
