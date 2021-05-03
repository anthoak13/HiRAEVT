/* Singelton factory for creating unpackers
 *
 * Adam Anthony 7/25/2019
 *
 */
#ifndef HTUNPACKERFACTORY_H
#define HTUNPACKERFACTORY_H

#include "TString.h"

#include "HTModuleUnpacker.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;
class TTree;

class HTUnpackerFactory {
public:
   static HTUnpackerFactory *Instance();

   // Creates a new unpacker and registers the output in the tree if passed
   HTModuleUnpacker *CreateUnpacker(json moduleDescription, TTree *tr = nullptr);

protected:
   HTUnpackerFactory();
   ~HTUnpackerFactory();

private:
   static HTUnpackerFactory *_instance;
};

#endif /** end ifndef HTDETECTORFACTORY_H **/
