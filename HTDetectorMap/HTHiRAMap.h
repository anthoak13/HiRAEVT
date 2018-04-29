#ifndef HTHIRAMAP_H
#define HTHIRAMAP_H

#include <HTDetectorMap.h>

class HTHiRAMap : public HTDetectorMap
{
public :
  HTHiRAMap(const char *, int);
  ~HTHiRAMap();

  int ParseMapLine(const char *) override;
  void Clear() override;


private :
  int fNumTelescopes;

};

#endif
