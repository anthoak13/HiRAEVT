#ifndef HTMUSICICMAPPER_H
#define HTMUSICICMAPPER_H

#include "HTDetectorMapper.h"

class HTMusicICMapper : public HTDetectorMapper {
public:
   HTMusicICMapper(const json &config);
   virtual ~HTMusicICMapper();

   virtual void MapAndCalibrate() override;
};

#endif //#ifndef HTMUSICICMAPPER_H
