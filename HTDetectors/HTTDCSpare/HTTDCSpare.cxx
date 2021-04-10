#include <HTTDCSpare.h>

#define dModule(det) ((HTTDCSpareMap *)fDetectorMapping)->GetModule(det)
#define dChannel(det) ((HTTDCSpareMap *)fDetectorMapping)->GetChannel(det)

//________________________________________________
HTTDCSpare::HTTDCSpare(const char *name) : HTDetector(name)
{
   fType.assign("HTTDCSpare");
}

//________________________________________________
HTTDCSpare::~HTTDCSpare()
{
   for (int i = 0; i < fNumDetectors; i++) {
      delete fSpareChannels[i];
   }
}

//________________________________________________
void HTTDCSpare::Clear() {}

//________________________________________________
void HTTDCSpare::InitTTreeBranch(TTree *theTree)
{
   fNumDetectors = ((HTTDCSpareMap *)fDetectorMapping)->GetNumChannels();

   for (int SpareCh = 0; SpareCh < fNumDetectors; SpareCh++) {
      HTTDCSpareChannel *newChannel =
         new HTTDCSpareChannel(((HTTDCSpareMap *)fDetectorMapping)->GetChannelName(SpareCh));
      fSpareChannels.push_back(newChannel);

      theTree->Branch(Form("%s.%s", fName.c_str(), fSpareChannels[SpareCh]->GetName()),
                      (Double_t *)fSpareChannels[SpareCh]->GetValuePointer(),
                      Form("%s.%s/D", fName.c_str(), fSpareChannels[SpareCh]->GetName()));
   }
   return;
}

//________________________________________________
void HTTDCSpare::BuildEvent()
{
   // Retrieving information from HTRootModule types
   for (int NumDet = 0; NumDet < fNumDetectors; NumDet++) {
      fSpareChannels[NumDet]->SetValue(((HTRootCAEN1x90 *)fModules[dModule(NumDet)])->GetData(dChannel(NumDet)));
   }

   // Fill Root Event structure to be written on the tree
   FillMappedData();

   return;
}

//________________________________________________
void HTTDCSpare::FillMappedData()
{
   // The entire data is used to fill the tree, no selection is made and no auxiliary data structures are needed
}

void HTTDCSpare::InitMapping()
{
   fDetectorMapping = new HTTDCSpareMap(fName);
}
