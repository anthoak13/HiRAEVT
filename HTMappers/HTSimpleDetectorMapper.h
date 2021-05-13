#ifndef HTSIMPLEDETECTORMAPPER_H
#define HTSIMPLEDETECTORMAPPER_H

// Mapper class for HTSimpleDetector

#include "HTDetectorMapper.h"

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class HTSimpleDetectorMapper : public HTDetectorMapper {
public:
   HTSimpleDetectorMapper(const json &config);
   virtual ~HTSimpleDetectorMapper();

   virtual void MapAndCalibrate() override;
};

#endif //#ifndef HTSIMPLEDETECTORMAPPER_H
