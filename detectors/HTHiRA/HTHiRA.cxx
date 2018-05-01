#include <HTHiRA.h>

#define dModuleEnergy(tel, csi) ((HTHiRAMap *)fDetectorMapping)->GetCsIEnergyModule(tel, csi)
#define dChannelEnergy(tel, csi) ((HTHiRAMap *)fDetectorMapping)->GetCsIEnergyChannel(tel, csi)
#define dModuleTime(tel, csi) ((HTHiRAMap *)fDetectorMapping)->GetCsITimeModule(tel, csi)
#define dChannelTime(tel, csi) ((HTHiRAMap *)fDetectorMapping)->GetCsITimeChannel(tel, csi)
#define dModuleEF(tel) ((HTHiRAMap *)fDetectorMapping)->GetEFModule(tel)
#define dModuleEB(tel) ((HTHiRAMap *)fDetectorMapping)->GetEBModule(tel)
#define dStripEF(tel, bank,chip,channel) ((HTHiRAMap *)fDetectorMapping)->GetStripEF(tel, bank,chip,channel)
#define dStripEB(tel, bank,chip,channel) ((HTHiRAMap *)fDetectorMapping)->GetStripEB(tel, bank,chip,channel)

//________________________________________________
HTHiRA::HTHiRA(const char * name, int num_telescopes) : HTDetector(name, num_telescopes),
fHiRACsI(0),
fevt(0)
{
  fHiRACsI=new HTHiRACsIArray[fNumDetectors];
  fevt=new HTHiRARootEvent(fNumDetectors);
  fType.assign("HTHiRA");
}

//________________________________________________
HTHiRA::~HTHiRA()
{
  if(fHiRACsI) delete fHiRACsI;
  if(fevt) delete fevt;
}

//________________________________________________
void HTHiRA::Clear()
{}


//________________________________________________
void HTHiRA::InitTTreeBranch(TTree * theTree)
{

  for(int NumTel=0; NumTel<fNumDetectors; NumTel++) {
    theTree->Branch(Form("%s.tele%d.",fName.c_str(),NumTel),"HTHiRAData",&(fevt->fHiRA[NumTel]),32768,3);
  }

  return;
}

//________________________________________________
void HTHiRA::BuildEvent()
{
  //Retrieving information from HTRootModule types loop on CsI only, strips are retrieved directly by FillMappedData
  for(int NumTel=0; NumTel<fNumDetectors; NumTel++) {
    for(int NumCsI=0; NumCsI< fHiRACsI->GetNumCsI(); NumCsI++) {
      HTHiRACsI * currCsI = fHiRACsI[NumTel].GetCsI(NumCsI);
      currCsI->SetEnergy(dModuleEnergy(NumTel, NumCsI)>=0 ? ((HTRootCAEN7xx *)fModules[dModuleEnergy(NumTel, NumCsI)])->GetData(dChannelEnergy(NumTel, NumCsI)) : -9999);
      currCsI->SetTime(dModuleTime(NumTel, NumCsI)>=0 ? ((HTRootCAEN1x90 *)fModules[dModuleTime(NumTel, NumCsI)])->GetData(dChannelTime(NumTel, NumCsI)) : -9999);
    }
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTHiRA::FillMappedData()
{
  //Retrieving information from HTHiRACsIArray and RBHINPHit to fill HTHiRAData object
  for(int NumTel=0; NumTel<fNumDetectors; NumTel++) {

    // Loop on CsIs
    fevt->fHiRA[NumTel].fCsI.fmulti=0;
    for(int NumCsI=0; NumCsI< fHiRACsI->GetNumCsI(); NumCsI++) {
      HTHiRACsI * currCsI = fHiRACsI[NumTel].GetCsI(NumCsI);
      if(currCsI->GetEnergy()>0 && currCsI->GetTime()!=-9999) {
        fevt->fHiRA[NumTel].fCsI.fnumcsi[fevt->fHiRA[NumTel].fCsI.fmulti]=NumCsI;
        fevt->fHiRA[NumTel].fCsI.fEnergy[fevt->fHiRA[NumTel].fCsI.fmulti]=currCsI->GetEnergy();
        fevt->fHiRA[NumTel].fCsI.fTime[fevt->fHiRA[NumTel].fCsI.fmulti]=currCsI->GetTime();
        fevt->fHiRA[NumTel].fCsI.fmulti++;
      }
    }

    //Loop on strips (here the logic is reversed, we loop on the module rather than on detector channels)
    TTreeReaderValue<RBHINPHit> * HINPDataEF = dModuleEF(NumTel)>=0 ? ((HTRootHINP *)fModules[dModuleEF(NumTel)])->GetDataPointer() : 0;
    fevt->fHiRA[NumTel].fEF.fmulti=0;
    for(int HINPhit=0; HINPhit<(*(*HINPDataEF)).fNHits; HINPhit++) {
      int StripToSet=dStripEF(NumTel,(*(*HINPDataEF)).fBank[HINPhit],(*(*HINPDataEF)).fChip[HINPhit],(*(*HINPDataEF)).fChannel[HINPhit]);
      if(StripToSet<0) continue;
      fevt->fHiRA[NumTel].fEF.fnumstrip[fevt->fHiRA[NumTel].fEF.fmulti]=StripToSet;
      fevt->fHiRA[NumTel].fEF.fEnergyHi[fevt->fHiRA[NumTel].fEF.fmulti]=(*(*HINPDataEF)).fEnergyHi[HINPhit];
      fevt->fHiRA[NumTel].fEF.fEnergyLo[fevt->fHiRA[NumTel].fEF.fmulti]=(*(*HINPDataEF)).fEnergyLo[HINPhit];
      fevt->fHiRA[NumTel].fEF.fTime[fevt->fHiRA[NumTel].fEF.fmulti]=(*(*HINPDataEF)).fTime[HINPhit];
      fevt->fHiRA[NumTel].fEF.fmulti++;
    }
    TTreeReaderValue<RBHINPHit> * HINPDataEB = dModuleEB(NumTel)>=0 ? ((HTRootHINP *)fModules[dModuleEB(NumTel)])->GetDataPointer() : 0;
    fevt->fHiRA[NumTel].fEB.fmulti=0;
    for(int HINPhit=0; HINPhit<(*(*HINPDataEB)).fNHits; HINPhit++) {
      int StripToSet=dStripEB(NumTel,(*(*HINPDataEB)).fBank[HINPhit],(*(*HINPDataEB)).fChip[HINPhit],(*(*HINPDataEB)).fChannel[HINPhit]);
      if(StripToSet<0) continue;
      fevt->fHiRA[NumTel].fEB.fnumstrip[fevt->fHiRA[NumTel].fEB.fmulti]=StripToSet;
      fevt->fHiRA[NumTel].fEB.fEnergyHi[fevt->fHiRA[NumTel].fEB.fmulti]=(*(*HINPDataEB)).fEnergyHi[HINPhit];
      fevt->fHiRA[NumTel].fEB.fEnergyLo[fevt->fHiRA[NumTel].fEB.fmulti]=(*(*HINPDataEB)).fEnergyLo[HINPhit];
      fevt->fHiRA[NumTel].fEB.fTime[fevt->fHiRA[NumTel].fEB.fmulti]=(*(*HINPDataEB)).fTime[HINPhit];
      fevt->fHiRA[NumTel].fEB.fmulti++;
    }

  }

  return;
}
