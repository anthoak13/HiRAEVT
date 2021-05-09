#ifndef HTMCPMAPPER_H
#define HTMCPMAPPER_H

#include "HTDetectorMapper.h"

#include <string>
#include <vector>

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class HTMcpMapper : public HTDetectorMapper {

public:
   HTMcpMapper(const json &config);
   virtual ~HTMcpMapper();

   virtual void MapAndCalibrate() override;

};

#endif //#ifndef HTMCPMAPPER_H
