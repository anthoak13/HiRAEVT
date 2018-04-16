#ifndef RBRUNINFO_H
#define RBRUNINFO_H

#include <RBDAQStackInfo.h>
#include <RBHINPUnpacker.h>
#include <RBPh7xxUnpacker.h>
#include <RBCAEN7xxUnpacker.h>
#include <RBCAEN1x90Unpacker.h>
#include <RBSisTimestampUnpacker.h>

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
  const char * GetEvtFilePath();
  int GetNStacks();
  RBDAQStackInfo * GetStackInfo(int);

  void SetEvtFilePath(const char *);

  void AddModuleToStackInfo(RBElectronics *);

private:
  const char * fRunTitle;
  int fRunNumber;
  const char * fEvtFilePath;
  bool fDAQLoaded;
  bool fPedestalsLoaded;
  bool fMappingLoaded;

  RBDAQStackInfo * fStackInfo;

};

#endif
