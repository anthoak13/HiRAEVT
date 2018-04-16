#ifndef RBRUNINFO_H
#define RBRUNINFO_H

#include <RBDAQStackInfo.h>

class RBRunInfo
{
public:
  RBRunInfo(int run_number);
  ~RBRunInfo();

  int LoadDAQSettings(const char *);
  int LoadPedestals(const char *);
  int LoadMapping(const char *);

  const char * GetRunTitle();
  int GetRunNumber();
  int GetNStacks();
  RBDAQStackInfo * GetStackInfo(int);

private:
  const char * fRunTitle;
  int fRunNumber;
  bool fDAQLoaded;
  bool fPedestalsLoaded;
  bool fMappingLoaded;
  
  RBDAQStackInfo * fStackInfo;

};

#endif
