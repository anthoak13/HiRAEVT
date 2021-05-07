#ifndef HTSIMPLEDETECTORMAPPER_H
#define HTSIMPLEDETECTORMAPPER_H

// Mapper class for HTSimpleDetector

#include "HTDetectorMapper.h"

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class HTMapper;

class HTSimpleDetectorMapper : public HTDetectorMapper {
private:
   const json &fConfig;

public:
   HTSimpleDetectorMapper(const json &config);
   virtual ~HTSimpleDetectorMapper();

   virtual void Map() override;
};

#endif //#ifndef HTSIMPLEDETECTORMAPPER_H
