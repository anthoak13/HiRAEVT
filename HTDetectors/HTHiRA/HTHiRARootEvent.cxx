#include <HTHiRARootEvent.h>

//________________________________________________
HTHiRAStripData::HTHiRAStripData() : fmulti(0)
{
   fnumstrip = new Int_t[N_STRIPS_PER_TELESCOPE];
   fEnergyHi = new UShort_t[N_STRIPS_PER_TELESCOPE];
   fEnergyLo = new UShort_t[N_STRIPS_PER_TELESCOPE];
   fTime = new UShort_t[N_STRIPS_PER_TELESCOPE];
}

//________________________________________________
HTHiRAStripData::~HTHiRAStripData()
{
   delete[] fnumstrip;
   delete[] fEnergyHi;
   delete[] fEnergyLo;
   delete[] fTime;
}

//________________________________________________
HTHiRACsIData::HTHiRACsIData() : fmulti(0)
{
   fnumcsi = new Int_t[N_CSIS_PER_TELESCOPE];
   fEnergy = new UShort_t[N_CSIS_PER_TELESCOPE];
   fTime = new Double_t[N_CSIS_PER_TELESCOPE];
}

//________________________________________________
HTHiRACsIData::~HTHiRACsIData()
{
   delete[] fnumcsi;
   delete[] fEnergy;
   delete[] fTime;
}

//________________________________________________
HTHiRAData::HTHiRAData() {}

//________________________________________________
HTHiRAData::~HTHiRAData() {}

//________________________________________________
HTHiRARootEvent::HTHiRARootEvent(int num_telescopes) : fNumTelescopes(num_telescopes), fHiRA(0)
{
   fHiRA = new HTHiRAData[fNumTelescopes];
}

//________________________________________________
HTHiRARootEvent::~HTHiRARootEvent()
{
   if (fHiRA)
      delete[] fHiRA;
}
