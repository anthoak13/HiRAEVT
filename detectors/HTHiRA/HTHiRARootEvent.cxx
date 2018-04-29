#include <HTHiRARootEvent.h>

/* WARNING: HiRA number of strips and CsIs per telescope is fixed */
const int N_STRIPS = 32;
const int N_CSI = 4;
/******************************************************************/

//________________________________________________
HTHiRAStrip::HTHiRAStrip() : fmulti(0)
{
  fnumstrip =new Int_t    [N_STRIPS];
  fEnergyHi =new UShort_t [N_STRIPS];
  fEnergyLo =new UShort_t [N_STRIPS];
  fTime     =new UShort_t [N_STRIPS];
}

//________________________________________________
HTHiRAStrip::~HTHiRAStrip()
{
  delete [] fnumstrip;
  delete [] fEnergyHi;
  delete [] fEnergyLo;
  delete [] fTime    ;
}

//________________________________________________
HTHiRACsI::HTHiRACsI() : fmulti(0)
{
  fnumcsi =new Int_t    [N_CSI];
  fEnergy =new UShort_t [N_CSI];
  fTime   =new Double_t [N_CSI];
}

//________________________________________________
HTHiRACsI::~HTHiRACsI()
{
  delete [] fnumcsi;
  delete [] fEnergy;
  delete [] fTime  ;
}

//________________________________________________
HTHiRAData::HTHiRAData()
{}

//________________________________________________
HTHiRAData::~HTHiRAData()
{}

//________________________________________________
HTHiRARootEvent::HTHiRARootEvent(int num_telescopes) :
fNumTelescopes(num_telescopes),
fHiRA(0)
{
  fHiRA=new HTHiRAData[fNumTelescopes];
}

//________________________________________________
HTHiRARootEvent::~HTHiRARootEvent()
{
  if(fHiRA) delete [] fHiRA;
}
