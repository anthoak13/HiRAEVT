#ifndef HTTDCSPAREMAP_H
#define HTTDCSPAREMAP_H

#include <HTDetectorMap.h>
#include <vector>

class HTTDCSpareMap : public HTDetectorMap
{
public :
  HTTDCSpareMap(const char *);
  ~HTTDCSpareMap();

  int ParseMapLine(const char *) override;
  void Clear() override;

  int GetModule(int num_ch) const {return fModule[num_ch];}
  int GetChannel(int num_ch) const {return fChannel[num_ch];}
  int GetNumChannels() const {return fNumChannels;}
  const char * GetChannelName(int num_ch) const {return fChannelName[num_ch].c_str();}

private :
  int fNumChannels;
  std::vector<int> fModule;
  std::vector<int> fChannel;
  std::vector<std::string> fChannelName;

};

#endif
