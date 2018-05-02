#include <HTMicroballArray.h>

//______________________________________________________________________________
HTMicroballArray::HTMicroballArray()
{
  fMicroballRing=(HTMicroballRing **) new HTMicroballRing *[N_MICROBALL_RINGS];

  for(int i=0; i<N_MICROBALL_RINGS; i++) {
    fMicroballRing[i]=(HTMicroballRing *) new HTMicroballRing(i,N_MICROBALL_DETS_PER_RING[i]);
  }
}

//______________________________________________________________________________
HTMicroballArray::~HTMicroballArray()
{
  if(!fMicroballRing) return;
  for(int i=0; i<N_MICROBALL_RINGS; i++) {
    if(fMicroballRing[i]) delete fMicroballRing[i];
  }
  if(!fMicroballRing) delete [] fMicroballRing;
}

//______________________________________________________________________________
HTMicroballRing * HTMicroballArray::GetRing(Int_t num_ring) const
{
  return fMicroballRing[num_ring-1];
}

//______________________________________________________________________________
Int_t HTMicroballArray::GetNumberRings() const
{
  return N_MICROBALL_RINGS;
}

//______________________________________________________________________________
void HTMicroballArray::Clear()
{
  for(int i=0; i<N_MICROBALL_RINGS; i++) {
    fMicroballRing[i]->Clear();
  }
}
