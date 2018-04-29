#include <HTMicroballRing.h>

//______________________________________________________________________________
HTMicroballRing::HTMicroballRing(Int_t ring_number, Int_t number_of_detectors) :
fNumRing(ring_number),
fNumDetectors(number_of_detectors)
{
  fMicroballDetector=(HTMicroballDetector **) new HTMicroballDetector *[fNumDetectors];

  for(int i=0; i<fNumDetectors; i++) {
    fMicroballDetector[i]=(HTMicroballDetector *) new HTMicroballDetector(i);
  }
}

//______________________________________________________________________________
HTMicroballRing::~HTMicroballRing()
{
  if(!fMicroballDetector) return;
  for(int i=0; i<fNumDetectors; i++) {
    if(fMicroballDetector[i]) delete fMicroballDetector[i];
  }

  if(!fMicroballDetector) delete [] fMicroballDetector;
}

//______________________________________________________________________________
HTMicroballDetector * HTMicroballRing::GetDetector(int num_det) const
{
  return fMicroballDetector[num_det-1];
}

//______________________________________________________________________________
Int_t HTMicroballRing::GetRingNumber() const
{
  return fNumRing+1;
}

//______________________________________________________________________________
Int_t HTMicroballRing::GetNumberDetectors() const
{
  return fNumDetectors;
}

//______________________________________________________________________________
void HTMicroballRing::Clear()
{
  for(int i=0; i<fNumDetectors; i++) {
    fMicroballDetector[i]->Clear();
  }
  return;
}
