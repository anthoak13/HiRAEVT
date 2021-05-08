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

private:
   Short_t GetEnergy(std::string moduleName, int ch);
   std::vector<Double_t> GetTime(std::string moduleName, int ch);
};

#endif //#ifndef HTMCPMAPPER_H
