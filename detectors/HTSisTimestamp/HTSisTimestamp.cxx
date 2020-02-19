#include <HTSisTimestamp.h>

#define dModuleTimestamp ((HTSisTimestampMap *)fDetectorMapping)->GetTimestampModule()
//#define dModuleTimestampKoreans ((HTSisTimestampMap *)fDetectorMapping)->GetTimestampKoreansModule()

//________________________________________________
HTSisTimestamp::HTSisTimestamp(const char * name, int num_detectors) : HTDetector(name, num_detectors),
								       fevt(0)
{
  fevt = new HTTStampRootEvent(num_detectors);
  fType.assign("SisTimestamp");
}

//________________________________________________
HTSisTimestamp::~HTSisTimestamp()
{
  if(fevt != nullptr)
    delete fevt;
}

//________________________________________________
void HTSisTimestamp::Clear()
{}

//________________________________________________
void HTSisTimestamp::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTTStampData",&(fevt->fSisTimestamp),32768,1);
}

//________________________________________________
void HTSisTimestamp::BuildEvent()
{
  HTSisTimestampMap *map = (HTSisTimestampMap*) fDetectorMapping;
  
  for (int detNum = 0; detNum < fNumDetectors; ++detNum)
  {
    //Check to make sure time module exists
    auto timestampModule = map->GetTimestampModule(detNum);
    auto timestampCh = map->GetTimestampChannel(detNum);
    if(timestampModule >= 0)
      fevt->fSisTimestamp.fTimestamp[detNum] =
	((HTRootSisTimestamp*)fModules[timestampModule])->GetData(timestampCh);
    else
      fevt->fSisTimestamp.fTimestamp[detNum] = 0;
  }
  
  //Fill Root Event structure to be written on the tree
  FillMappedData();
  
  return;
}

//________________________________________________
void HTSisTimestamp::FillMappedData()
{
  (fevt->fSisTimestamp).fMulti = fNumDetectors;

  //(fevt->fSisTimestamp).fTimestampKoreans=fTimestampKoreans;
  return;
}

void HTSisTimestamp::InitMapping()
{
  fDetectorMapping = new HTSisTimestampMap(fName, fNumDetectors);
}
