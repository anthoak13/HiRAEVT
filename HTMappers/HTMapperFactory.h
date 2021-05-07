/* Singelton factory for creating detectors
 *
 * Adam Anthony 5/6/2021
 *
 */
#ifndef HTDETECTORMAPPERFACTORY_H
#define HTDETECTORMAPPERFACTORY_H

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class TTree;
class HTDetectorMapper;

class HTMapperFactory {
public:
   static HTMapperFactory *Instance();

   HTDetectorMapper *CreateDetector(const json &detConfig, TTree *tr = nullptr);

protected:
   HTMapperFactory() {}
   ~HTMapperFactory() {}

private:
   static HTMapperFactory *_instance;
};

#endif /** end ifndef HTDETECTORFACTORY_H **/
