#ifndef HTSISTIMESTAMPE15190MAP_H
#define HTSISTIMESTAMPE15190MAP_H

#include <HTDetectorMap.h>

class HTSisTimestampe15190Map : public HTDetectorMap
{
public :
  HTSisTimestampe15190Map(const std::string&);
  ~HTSisTimestampe15190Map();

  int ParseMapLine(const char *) override;

  int GetTimestampModule() const;
  int GetTimestampKoreansModule() const;

private :
  int fTimestampModule;
  int fTimestampKoreansModule;

};

#endif
