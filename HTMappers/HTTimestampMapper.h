#ifndef HTTIMESTAMPMAPPER_H
#define HTTIMESTAMPMAPPER_H

// Mapper class for HTTimestamp

#include "HTDetectorMapper.h"

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class HTTimestampMapper : public HTDetectorMapper {
public:
   HTTimestampMapper(const json &config);
   virtual ~HTTimestampMapper();

   virtual void MapAndCalibrate() override;
};

#endif //#ifndef HTTIMESTAMPMAPPER_H
