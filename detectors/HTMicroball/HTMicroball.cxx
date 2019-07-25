#include <HTMicroball.h>

// WARNING: Detector numbering within a ring starts from 1 but the arrays start from 0

#define dModuleFast(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetFastModule(ring, det)
#define dChannelFast(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetFastChannel(ring, det)
#define dModuleTail(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetTailModule(ring, det)
#define dChannelTail(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetTailChannel(ring, det)
#define dModuleTime(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetTimeModule(ring, det)
#define dChannelTime(ring, det) ((HTMicroballMap *)fDetectorMapping)->GetTimeChannel(ring, det)

//________________________________________________
HTMicroball::HTMicroball(const char * name) : HTDetector(name),
fMicroball(0),
fevt(0),
fNumDetectors(TOT_NUMER_MICROBALL_DETECTORS)
{
  fMicroball=new HTMicroballArray();
  fevt=new HTMicroballRootEvent(fNumDetectors);
  fType.assign("HTMicroball");
}

//________________________________________________
HTMicroball::~HTMicroball()
{
  if(fMicroball) delete [] fMicroball;
  if(fevt) delete fevt;
}

//________________________________________________
void HTMicroball::Clear()
{

}

//________________________________________________
void HTMicroball::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTMicroballData",&(fevt->fMicroball),32768,1);
  return;
}

//________________________________________________
void HTMicroball::BuildEvent()
{
  //Retrieving information from HTRootModule types
  for(int NumRing=0; NumRing<N_MICROBALL_RINGS; NumRing++) {
    HTMicroballRing * currRing =fMicroball->GetRing(NumRing+1);
    for(int NumDet=0; NumDet<N_MICROBALL_DETS_PER_RING[NumRing]; NumDet++) {
      HTMicroballDetector * currDet = currRing->GetDetector(NumDet+1); //WARNING: uBall detectors start from 1
      currDet->SetTail(dModuleTail(NumRing, NumDet)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleTail(NumRing, NumDet)])->GetData(dChannelTail(NumRing, NumDet)) : -9999);
      currDet->SetFast(dModuleFast(NumRing, NumDet)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleFast(NumRing, NumDet)])->GetData(dChannelFast(NumRing, NumDet)) : -9999);
      currDet->SetTime(dModuleTime(NumRing, NumDet)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleTime(NumRing, NumDet)])->GetData(dChannelTime(NumRing, NumDet)) : -9999);
    }
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTMicroball::FillMappedData()
{
  //Retrieving information from HTMicroballArray to fill HTMicroballData object
  fevt->fMicroball.fmulti=0;
  for(int NumRing=0; NumRing<fMicroball->GetNumberRings(); NumRing++) {
    HTMicroballRing * RingToFill =fMicroball->GetRing(NumRing+1);
    for(int NumDet=0; NumDet<N_MICROBALL_DETS_PER_RING[NumRing]; NumDet++) {
      HTMicroballDetector * DetToFill = RingToFill->GetDetector(NumDet+1); //WARNING: uBall detectors start from 1
      if((DetToFill->GetTail()>0 || DetToFill->GetFast()>0) && DetToFill->GetTime()>0)
      {
        fevt->fMicroball.fnumring[fevt->fMicroball.fmulti]=NumRing+1; //WARNING: rings are counted from 1
        fevt->fMicroball.fnumdet[fevt->fMicroball.fmulti]=NumDet+1; //WARNING: detectors are counted from 1 in each ring
        fevt->fMicroball.fTail[fevt->fMicroball.fmulti]=DetToFill->GetTail();
        fevt->fMicroball.fFast[fevt->fMicroball.fmulti]=DetToFill->GetFast();
        fevt->fMicroball.fTime[fevt->fMicroball.fmulti]=DetToFill->GetTime();
        fevt->fMicroball.fmulti++;
      }
    }
  }

  return;
}

void HTMicroball::InitMapping()
{
  fDetectorMapping = new HTMicroballMap(fName);
}
