#include <RBModuleInfo.h>

//________________________________________________
RBModuleInfo::RBModuleInfo() :
fNumCh(0),
fModuleVSN(0),
fModule(0),
fModuleMapping(0),
fModulePedestal(0)
{}

//________________________________________________
RBModuleInfo::~RBModuleInfo()
{
  delete fModule;
  for (int i=0; i<fNumCh; i++) {
    if(fModuleMapping) {
      delete fModuleMapping;
    }
    if(fModulePedestal){
      delete fModulePedestal;
    }
  }
}

//________________________________________________
void RBModuleInfo::SetModule(RBElectronics * newModule)
{
  fModule=newModule;
}

//________________________________________________
void RBModuleInfo::SetNumCh(int num_ch)
{
  fNumCh=num_ch;
}

//________________________________________________
void RBModuleInfo::SetVSN(int new_VSN)
{
  fModuleVSN=new_VSN;
}

//________________________________________________
void RBModuleInfo::SetModuleType(std::string modType)
{
  fModuleType.assign(modType);
}

//________________________________________________
void RBModuleInfo::SetModuleType(const char * modType)
{
  fModuleType.assign(modType);
}

//________________________________________________
void RBModuleInfo::SetModuleName(std::string modName)
{
  fModuleName.assign(modName);
}

//________________________________________________
void RBModuleInfo::SetModuleName(const char * modName)
{
  fModuleName.assign(modName);
}

//________________________________________________
void RBModuleInfo::SetChannelMapping(int ch, std::string newChMapping)
{
  fModuleMapping[ch].assign(newChMapping);
}

//________________________________________________
void RBModuleInfo::SetChannelMapping(int ch, const char * newChMapping)
{
  fModuleMapping[ch].assign(newChMapping);
}

//________________________________________________
void RBModuleInfo::SetChannelPedestal(int ch, double newPedestal)
{
  fModulePedestal[ch]=newPedestal;
}

//________________________________________________
RBElectronics * RBModuleInfo::GetModule() const
{
  return fModule;
}

//________________________________________________
int RBModuleInfo::GetVSN() const
{
  return fModuleVSN;
}

//________________________________________________
int RBModuleInfo::GetNumCh() const
{
  return fNumCh;
}

//________________________________________________
const char * RBModuleInfo::GetModuleType() const
{
  return fModuleType.c_str();
}

//________________________________________________
const char * RBModuleInfo::GetModuleName() const
{
  return fModuleName.c_str();
}

//________________________________________________
const char * RBModuleInfo::GetModuleChMapping(int ch) const
{
  return fModuleMapping[ch].c_str();
}

//________________________________________________
double RBModuleInfo::GetModuleChPedestal(int ch) const
{
  return fModulePedestal[ch];
}
