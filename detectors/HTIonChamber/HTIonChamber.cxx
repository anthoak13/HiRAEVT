#include <HTIonChamber.h>

//________________________________________________
HTIonChamber::HTIonChamber(const char * name, int num_detectors) : HTDetector(name, num_detectors),
								   fevt(0)
{
  fevt = new HTIonChamberRootEvent(fNumDetectors);
  fType.assign("HTIonChamber");
}

//________________________________________________
HTIonChamber::~HTIonChamber()
{
  if( fevt != nullptr )
    delete fevt;
}

//________________________________________________
void HTIonChamber::Clear()
{}

//________________________________________________
void HTIonChamber::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTIonChamberData",&(fevt->fIonChamber),32768,1);
  return;
}

//________________________________________________
void HTIonChamber::BuildEvent()
{
  //Retrieving information from HTRootModule types
  for(int detNum=0; detNum < fNumDetectors; detNum++)
  {
    HTIonChamberMap* map = (HTIonChamberMap*) fDetectorMapping;
    
    //If the energy module exists, grab the energy
    if(map->GetEnergyModule(detNum) >= 0)
      fevt->fIonChamber.fE[detNum] = ((HTRootMADC32 *)fModules[map->GetEnergyModule(detNum)])->
	GetData(map->GetEnergyChannel(detNum));
    else
      //std::cout << "Failed to find energy module for " << detNum << std::endl;
      fevt->fIonChamber.fE[detNum] = -9999;

    //If the time module exists get the time
    if(map->GetTimeModule(detNum) >= 0)
      fevt->fIonChamber.fTime[detNum] = ((HTRootCAEN1x90 *)fModules[map->GetTimeModule(detNum)])->
	GetData(map->GetTimeChannel(detNum));
    else
      fevt->fIonChamber.fTime[detNum] = -9999;

    //Set the det num
    fevt->fIonChamber.fDetNum[detNum] = detNum;
  }

  //Fill Root Event structure to be written on the tree
  FillMappedData();

  return;
}

//________________________________________________
void HTIonChamber::FillMappedData()
{
  //Retrieving information from HTIonChamberCluster to fill HTIonChamberData object
  fevt->fIonChamber.fMulti = fNumDetectors;
  
/*  for(int detNum=0; detNum<fNumDetectors; detNum++)
  {
    if(fevt->E[detNum] > 0 && fevt->fTime[detNum] != -9999)
    {
      fevt->fIonChamber.fE[fevt->]=DetToFill->GetE();
      fevt->fIonChamber.fTime[fevt->fIonChamber.fmulti]=DetToFill->GetTime();
      fevt->fIonChamber.fmulti++;
    }
  }
*/
  return;
}
void HTIonChamber::InitMapping()
{
  fDetectorMapping = new HTIonChamberMap(fName, fNumDetectors);
}

void HTIonChamber::InitCalibration()
{
  fDetectorCalibration = new HTIonChamberCalibration();
}
