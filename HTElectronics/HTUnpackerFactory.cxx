#include "HTUnpackerFactory.h"

#include "HTCAEN1x90Unpacker.h"
#include "HTCAEN7xxUnpacker.h"
#include "HTMADC32Unpacker.h"
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

HTModuleUnpacker *HTUnpackerFactory::CreateUnpacker(json moduleDescription)
{
   TString unpackerType = moduleDescription["moduleType"].get<std::string>();

   if (unpackerType.EqualTo("HTSisTimestampUnpacker"))
      return new HTSisTimestampUnpacker(moduleDescription);

   if (unpackerType.EqualTo("HTCAEN1x90Unpacker"))
      return new HTCAEN1x90Unpacker(moduleDescription);

   if (unpackerType.EqualTo("HTCAEN7xxUnpacker"))
      return new HTCAEN7xxUnpacker(moduleDescription);

   if (unpackerType.EqualTo("HTMADC32Unpacker"))
      return new HTMADC32Unpacker(moduleDescription);

   return nullptr;
}
