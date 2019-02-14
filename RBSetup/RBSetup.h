#ifndef ____RBSetup__
#define ____RBSetup__

#include <stdio.h>

#include <RBUSBStack.h>
#include <RBElectronics.h>
#include <RBTimestamp.h>
#include <RBUSBStackMarker.h>
#include <RBHINPUnpacker.h>
#include <RBPh7xxUnpacker.h>
#include <RBCAEN7xxUnpacker.h>
#include <RBCAEN1x90Unpacker.h>
#include <RBMADC32Unpacker.h>
#include <RBSisTimestampUnpacker.h>
#include <HTRunInfo.h>
#include <HTExperimentInfo.h>
#include <HTDAQStackInfo.h>
#include <HTModuleInfo.h>

#include <TNamed.h>
#include <HTShared.h>
#include <RBExperiment.h>
#include <HTRunInfo.h>

class RBSetup : public TNamed
{
private:

public:
  RBSetup();
  ~RBSetup();

  void Print(){};

  ClassDef(RBSetup,1);
};


#endif /* defined(____RBSetup__) */
