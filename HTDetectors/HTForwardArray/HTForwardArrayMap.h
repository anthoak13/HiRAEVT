#ifndef HTFORWARDARRAYMAP_H
#define HTFORWARDARRAYMAP_H

#include <HTDetectorMap.h>

class HTForwardArrayMap : public HTDetectorMap {
public:
   HTForwardArrayMap(const std::string &, int);
   ~HTForwardArrayMap();

   int ParseMapLine(const char *) override;
   void Clear() override;

   int GetEnergyModule(int num_det) const { return fEnergyModule[num_det]; }
   int GetEnergyChannel(int num_det) const { return fEnergyChannel[num_det]; }
   int GetTimeModule(int num_det) const { return fTimeModule[num_det]; }
   int GetTimeChannel(int num_det) const { return fTimeChannel[num_det]; }

private:
   int fNumDetectors;
   int *fEnergyModule;
   int *fEnergyChannel;
   int *fTimeModule;
   int *fTimeChannel;
};

#endif
