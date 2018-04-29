#include <HTForwardArrayCluster.h>

//______________________________________________________________________________
HTForwardArrayCluster::HTForwardArrayCluster(int number_of_detectors) :
fNumDetectors(number_of_detectors)
{
  fForwardArrayDetector=(HTForwardArrayDetector **) new HTForwardArrayDetector *[fNumDetectors];

  for(int i=0; i<fNumDetectors; i++) {
    fForwardArrayDetector[i]=(HTForwardArrayDetector *) new HTForwardArrayDetector(i);
  }
}

//______________________________________________________________________________
HTForwardArrayCluster::~HTForwardArrayCluster()
{
  if(!fForwardArrayDetector) return;
  for(int i=0; i<fNumDetectors; i++)
  {
    if(fForwardArrayDetector[i]) delete fForwardArrayDetector[i];
  }

  if(!fForwardArrayDetector) delete [] fForwardArrayDetector;
}

//______________________________________________________________________________
HTForwardArrayDetector * HTForwardArrayCluster::GetDetector(Int_t num_det) const
{
  return fForwardArrayDetector[num_det];
}

//______________________________________________________________________________
Int_t HTForwardArrayCluster::GetNumberDetectors() const
{
  return fNumDetectors;
}

//______________________________________________________________________________
void HTForwardArrayCluster::Clear()
{
  for(int i=0; i<fNumDetectors; i++) {
    fForwardArrayDetector[i]->Clear();
  }
}
