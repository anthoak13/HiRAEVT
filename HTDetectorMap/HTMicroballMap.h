#ifndef HTMICROBALLMAP_H
#define HTMICROBALLMAP_H

#include <HTDetectorMap.h>

class HTMicroballMap : public HTDetectorMap
{
public :
  HTMicroballMap(const char *);
  ~HTMicroballMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetFastModule(int num_ring, int num_det) const {return fFastModule[num_ring][num_det];}
  int GetFastChannel(int num_ring, int num_det) const {return fFastChannel[num_ring][num_det];}
  int GetTailModule(int num_ring, int num_det) const {return fTailModule[num_ring][num_det];}
  int GetTailChannel(int num_ring, int num_det) const {return fTailChannel[num_ring][num_det];}
  int GetTimeModule(int num_ring, int num_det) const {return fTimeModule[num_ring][num_det];}
  int GetTimeChannel(int num_ring, int num_det) const {return fTimeChannel[num_ring][num_det];}

private :
  int fNumDetectors;
  int **fFastModule;
  int **fFastChannel;
  int **fTailModule;
  int **fTailChannel;
  int **fTimeModule;
  int **fTimeChannel;

};

#endif
