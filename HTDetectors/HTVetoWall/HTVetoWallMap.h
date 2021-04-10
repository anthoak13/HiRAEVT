#ifndef HTVETOWALLMAP_H
#define HTVETOWALLMAP_H

#include <HTDetectorMap.h>

class HTVetoWallMap : public HTDetectorMap {
public:
   HTVetoWallMap(const std::string &, int);
   ~HTVetoWallMap();

   int ParseMapLine(const char *) override;
   void Clear() override;

   int GetBottomModule(int num_bar) const { return fBottomModule[num_bar]; }
   int GetBottomChannel(int num_bar) const { return fBottomChannel[num_bar]; }
   int GetTopModule(int num_bar) const { return fTopModule[num_bar]; }
   int GetTopChannel(int num_bar) const { return fTopChannel[num_bar]; }
   int GetTimeBottomModule(int num_bar) const { return fBottomTimeModule[num_bar]; }
   int GetTimeBottomChannel(int num_bar) const { return fBottomTimeChannel[num_bar]; }
   int GetTimeTopModule(int num_bar) const { return fTopTimeModule[num_bar]; }
   int GetTimeTopChannel(int num_bar) const { return fTopTimeChannel[num_bar]; }

private:
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
