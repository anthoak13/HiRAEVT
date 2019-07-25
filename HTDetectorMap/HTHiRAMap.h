#ifndef HTHIRAMAP_H
#define HTHIRAMAP_H

#include <HTDetectorMap.h>
#include <HTShared.h>

class HTHiRAMap : public HTDetectorMap
{
public :
  HTHiRAMap(const std::string&, int);
  ~HTHiRAMap();

  int GetCsIEnergyModule(int tel, int csi) const {return fCsIEnergyModule[tel][csi];}
  int GetCsIEnergyChannel(int tel, int csi) const {return fCsIEnergyChannel[tel][csi];}
  int GetCsITimeModule(int tel, int csi) const {return fCsITimeModule[tel][csi];}
  int GetCsITimeChannel(int tel, int csi) const {return fCsITimeChannel[tel][csi];}
  int GetEFModule(int tel) const {return fModuleEF[tel];}
  int GetEBModule(int tel) const {return fModuleEB[tel];}
  int GetStripEF(int tel, int bank, int chip, int channel) const {return fStripEF[tel][bank][chip-1][channel];}
  int GetStripEB(int tel, int bank, int chip, int channel) const {return fStripEB[tel][bank][chip-1][channel];}

  int ParseMapLine(const char *) override;
  void Clear() override;

private :
  int fNumTelescopes;
  int fNumStripsperTelescope;
  int fNumCsIperTelescope;
  int **fCsIEnergyModule;
  int **fCsIEnergyChannel;
  int **fCsITimeModule;
  int **fCsITimeChannel;
  int * fModuleEF;
  int * fModuleEB;
  int ****fStripEF;
  int ****fStripEB;

};

#endif
