#include <RBRunInfo.h>

//________________________________________________
RBRunInfo::RBRunInfo(int run_number) : 
fRunTitle(0),
fRunNumber(run_number),
fDAQLoaded(false),
fPedestalsLoaded(false),
fMappingLoaded(false)
{}

//________________________________________________
RBRunInfo::~RBRunInfo()
{}

//________________________________________________
int RBRunInfo::LoadDAQSettings(const char * file_name)
{
  fDAQLoaded=true;
  return 0;
}

//________________________________________________
int RBRunInfo::LoadPedestals(const char * file_name)
{
  if(!fDAQLoaded) return -1;
  fMappingLoaded=true;
  return 0;
}

//________________________________________________
int RBRunInfo::LoadMapping(const char * file_name)
{
  if(!fDAQLoaded) return -1;
  fPedestalsLoaded=true;
  return 0;
}

