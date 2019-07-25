#ifndef HTNEUTRONWALLMAP_H
#define HTNEUTRONWALLMAP_H

#include <HTDetectorMap.h>

class HTNeutronWallMap : public HTDetectorMap
{
public :
  HTNeutronWallMap(const std::string&, int);
  ~HTNeutronWallMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetLeftModule(int num_bar) const {return fLeftModule[num_bar];}
  int GetLeftChannel(int num_bar) const {return fLeftChannel[num_bar];}
  int GetFastLeftModule(int num_bar) const {return fLeftFastModule[num_bar];}
  int GetFastLeftChannel(int num_bar) const {return fLeftFastChannel[num_bar];}
  int GetRightModule(int num_bar) const {return fRightModule[num_bar];}
  int GetRightChannel(int num_bar) const {return fRightChannel[num_bar];}
  int GetFastRightModule(int num_bar) const {return fRightFastModule[num_bar];}
  int GetFastRightChannel(int num_bar) const {return fRightFastChannel[num_bar];}
  int GetTimeLeftModule(int num_bar) const {return fLeftTimeModule[num_bar];}
  int GetTimeLeftChannel(int num_bar) const {return fLeftTimeChannel[num_bar];}
  int GetTimeRightModule(int num_bar) const {return fRightTimeModule[num_bar];}
  int GetTimeRightChannel(int num_bar) const {return fRightTimeChannel[num_bar];}

private :
  int fNumBars;
  int *fLeftModule;
  int *fLeftChannel;
  int *fLeftFastModule;
  int *fLeftFastChannel;
  int *fRightModule;
  int *fRightChannel;
  int *fRightFastModule;
  int *fRightFastChannel;
  int *fLeftTimeModule;
  int *fLeftTimeChannel;
  int *fRightTimeModule;
  int *fRightTimeChannel;

};

#endif
