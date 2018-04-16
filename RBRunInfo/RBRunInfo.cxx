#include <RBRunInfo.h>

//________________________________________________
RBRunInfo::RBRunInfo(int run_number, const char * run_title) :
fRunNumber(run_number),
fNStacks(0),
fDAQLoaded(false),
fPedestalsLoaded(false),
fMappingLoaded(false)
{
  SetRunTitle(run_title);
}

//________________________________________________
RBRunInfo::~RBRunInfo()
{
  for(int i=0; i< fNStacks; i++) {
    if (fStackInfo[i]) {
      delete fStackInfo[i];
    }
  }
}

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

//________________________________________________
void RBRunInfo::SetRunTitle(const char * run_title)
{
  fRunTitle.assign(run_title);
}

//________________________________________________
void RBRunInfo::SetEvtFilePath(const char * file_name)
{
  fEvtFilePath.assign(file_name);
}

//________________________________________________
const char * RBRunInfo::GetEvtFilePath() const
{
  return fEvtFilePath.c_str();
}

//________________________________________________
const char * RBRunInfo::GetRunTitle() const
{
  return fRunTitle.c_str();
}

//________________________________________________
int RBRunInfo::GetRunNumber() const
{
  return fRunNumber;
}

//________________________________________________
int RBRunInfo::GetNStacks() const
{
  return fNStacks;
}
