#ifndef HTSISTIMESTAMPMAP_H
#define HTSISTIMESTAMPMAP_H

#include <HTDetectorMap.h>

class HTSisTimestampMap : public HTDetectorMap
{
public :
  HTSisTimestampMap(const std::string&, int);
  ~HTSisTimestampMap();

  int ParseMapLine(const char *) override;

  int GetTimestampModule(int detNum) const {return fTimestampModule[detNum]; };
  int GetTimestampChannel(int detNum) const {return fTimestampChannel[detNum]; };

  void Clear() override;
private :
  int fNumDetectors;
  int * fTimestampModule;
  int * fTimestampChannel;

};

#endif
