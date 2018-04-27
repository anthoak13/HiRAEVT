#ifndef HTNEUTRONWALLMAP_H
#define HTNEUTRONWALLMAP_H

#include <HTDetectorMap.h>

class HTNeutronWallMap : public HTDetectorMap
{
public :
  HTNeutronWallMap(const char *);
  ~HTNeutronWallMap();

  int ParseMapLine(const char *) override;

  int GetLeftModule() const {return fLeftModule;}
  int GetLeftChannel() const {return fLeftChannel;}
  int GetLeftFastModule() const {return fLeftFastModule;}
  int GetLeftFastChannel() const {return fLeftFastChannel;}
  int GetRightModule() const {return fRightModule;}
  int GetRightChannel() const {return fRightChannel;}
  int GetRightFastModule() const {return fRightFastModule;}
  int GetRightFastChannel() const {return fRightFastChannel;}
  int GetLeftTimeModule() const {return fLeftTimeModule;}
  int GetLeftTimeChannel() const {return fLeftTimeChannel;}
  int GetRightTimeModule() const {return fRightTimeModule;}
  int GetRightTimeChannel() const {return fRightTimeChannel;}

private :
  int fLeftModule;
  int fLeftChannel;
  int fLeftFastModule;
  int fLeftFastChannel;
  int fRightModule;
  int fRightChannel;
  int fRightFastModule;
  int fRightFastChannel;
  int fLeftTimeModule;
  int fLeftTimeChannel;
  int fRightTimeModule;
  int fRightTimeChannel;

};

#endif
