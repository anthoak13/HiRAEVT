#include <HTMicroballMap.h>

/* WARNING: uBall number of rings and detectors per ring is fixed */
const int N_RINGS = 9;
const int N_DETS[] = {6, 10, 12, 12, 14, 14, 12, 10, 6};
// Detector numbering within a ring starts from 1 but the arrays start from 0
/******************************************************************/

//________________________________________________
HTMicroballMap::HTMicroballMap(const std::string& name) : HTDetectorMap(name),
fFastModule(0),
fFastChannel(0),
fTailModule(0),
fTailChannel(0),
fTimeModule(0),
fTimeChannel(0)
{
  fFastModule=new int*[N_RINGS];
  fFastChannel=new int*[N_RINGS];
  fTailModule=new int*[N_RINGS];
  fTailChannel=new int*[N_RINGS];
  fTimeModule=new int*[N_RINGS];
  fTimeChannel=new int*[N_RINGS];
  for(int i=0; i<N_RINGS; i++) {
    fFastModule[i]=new int[N_DETS[i]];
    fFastChannel[i]=new int[N_DETS[i]];
    fTailModule[i]=new int[N_DETS[i]];
    fTailChannel[i]=new int[N_DETS[i]];
    fTimeModule[i]=new int[N_DETS[i]];
    fTimeChannel[i]=new int[N_DETS[i]];
  }

  Clear();
}

//________________________________________________
HTMicroballMap::~HTMicroballMap()
{
  for(int i=0; i<N_RINGS; i++) {
    if(fFastModule[i]) delete [] fFastModule[i];
    if(fFastChannel[i]) delete [] fFastChannel[i];
    if(fTailModule[i]) delete [] fTailModule[i];
    if(fTailChannel[i]) delete [] fTailChannel[i];
    if(fTimeModule[i]) delete [] fTimeModule[i];
    if(fTimeChannel[i]) delete [] fTimeChannel[i];
  }
  if(fFastModule) delete [] fFastModule;
  if(fFastChannel) delete [] fFastChannel;
  if(fTailModule) delete [] fTailModule;
  if(fTailChannel) delete [] fTailChannel;
  if(fTimeModule) delete [] fTimeModule;
  if(fTimeChannel)   delete [] fTimeChannel;
}

//________________________________________________
void HTMicroballMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<N_RINGS; i++) {
    for(int j=0; j<N_DETS[i]; j++) {
      fFastModule[i][j]=-1;
      fFastChannel[i][j]=-1;
      fTailModule[i][j]=-1;
      fTailChannel[i][j]=-1;
      fTimeModule[i][j]=-1;
      fTimeChannel[i][j]=-1;
    }
  }
}

//________________________________________________
int HTMicroballMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string DetectorToSet;
  std::string ModuleName;
  std::string ModuleChannelString;
  LineStream>>DetectorName>>ChName>>DetectorToSet>>ModuleName>>ModuleChannelString;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));
  ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));

  int RingNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("R")+1, DetectorToSet.find("_")-(DetectorToSet.find("R")+1)))-1;
  int DetectorNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("_")+1))-1;
  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];
  int ModuleChannel=std::stoi(ModuleChannelString);

  if(ChName.compare("FAST")==0) {
    fFastModule[RingNumber][DetectorNumber]=ModuleNumber;
    fFastChannel[RingNumber][DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("TAIL")==0) {
    fTailModule[RingNumber][DetectorNumber]=ModuleNumber;
    fTailChannel[RingNumber][DetectorNumber]=ModuleChannel;
  } else if (ChName.compare("TIME")==0) {
    fTimeModule[RingNumber][DetectorNumber]=ModuleNumber;
    fTimeChannel[RingNumber][DetectorNumber]=ModuleChannel;
  }



  return 1;
}
