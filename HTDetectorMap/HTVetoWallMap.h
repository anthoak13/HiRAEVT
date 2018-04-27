#ifndef HTVETOWALLMAP_H
#define HTVETOWALLMAP_H

#include <HTDetectorMap.h>

class HTVetoWallMap : public HTDetectorMap
{
public :
  HTVetoWallMap(const char *);
  ~HTVetoWallMap();

  int ParseMapLine(const char *) override;

  int GetBottomModule() const {return fBottomModule;}
  int GetBottomChannel() const {return fBottomChannel;}
  int GetTopModule() const {return fTopModule;}
  int GetTopChannel() const {return fTopChannel;}
  int GetBottomTimeModule() const {return fBottomTimeModule;}
  int GetBottomTimeChannel() const {return fBottomTimeChannel;}
  int GetTopTimeModule() const {return fTopTimeModule;}
  int GetTopTimeChannel() const {return fTopTimeChannel;}

private :
  int fBottomModule;
  int fBottomChannel;
  int fTopModule;
  int fTopChannel;
  int fBottomTimeModule;
  int fBottomTimeChannel;
  int fTopTimeModule;
  int fTopTimeChannel;

};

#endif
