#ifndef HTVETOWALLMAP_H
#define HTVETOWALLMAP_H

#include <HTDetectorMap.h>

class HTVetoWallMap : public HTDetectorMap
{
public :
  HTVetoWallMap(const char *, int);
  ~HTVetoWallMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetBottomModule(int num_bar) const {return fBottomModule[num_bar];}
  int GetBottomChannel(int num_bar) const {return fBottomChannel[num_bar];}
  int GetTopModule(int num_bar) const {return fTopModule[num_bar];}
  int GetTopChannel(int num_bar) const {return fTopChannel[num_bar];}
  int GetBottomTimeModule(int num_bar) const {return fBottomTimeModule[num_bar];}
  int GetBottomTimeChannel(int num_bar) const {return fBottomTimeChannel[num_bar];}
  int GetTopTimeModule(int num_bar) const {return fTopTimeModule[num_bar];}
  int GetTopTimeChannel(int num_bar) const {return fTopTimeChannel[num_bar];}

private :
  int fNumBars;
  int *fBottomModule;
  int *fBottomChannel;
  int *fTopModule;
  int *fTopChannel;
  int *fBottomTimeModule;
  int *fBottomTimeChannel;
  int *fTopTimeModule;
  int *fTopTimeChannel;

};

#endif
