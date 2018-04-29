#include <HTMicroballArray.h>

/* WARNING: uBall number of rings and detectors per ring is fixed */
const int N_RINGS = 9;
const int N_DETS[] = {6, 10, 12, 12, 14, 14, 12, 10, 6};
// Detector numbering within a ring starts from 1 but the arrays start from 0
/******************************************************************/

//______________________________________________________________________________
HTMicroballArray::HTMicroballArray()
{
  fMicroballRing=(HTMicroballRing **) new HTMicroballRing *[N_RINGS];

  for(int i=0; i<N_RINGS; i++) {
    fMicroballRing[i]=(HTMicroballRing *) new HTMicroballRing(i,N_DETS[i]);
  }
}

//______________________________________________________________________________
HTMicroballArray::~HTMicroballArray()
{
  if(!fMicroballRing) return;
  for(int i=0; i<N_RINGS; i++) {
    if(fMicroballRing[i]) delete fMicroballRing[i];
  }
  if(!fMicroballRing) delete [] fMicroballRing;
}

//______________________________________________________________________________
HTMicroballRing * HTMicroballArray::GetRing(Int_t num_ring) const
{
  return fMicroballRing[num_ring];
}

//______________________________________________________________________________
Int_t HTMicroballArray::GetNumberRings() const
{
  return N_RINGS;
}

//______________________________________________________________________________
void HTMicroballArray::Clear()
{
  for(int i=0; i<N_RINGS; i++) {
    fMicroballRing[i]->Clear();
  }
}
