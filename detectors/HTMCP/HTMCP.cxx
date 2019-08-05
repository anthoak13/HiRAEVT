#include <HTMCP.h>

//________________________________________________
HTMCP::HTMCP(const char * name, int numDetectors) : HTDetector(name, numDetectors)
{
  fevt = new HTMCPRootEvent(fNumDetectors);
  fType.assign("HTMCP");
}

//________________________________________________
HTMCP::~HTMCP()
{
  if( fevt != nullptr )
    delete fevt;
}

//________________________________________________
void HTMCP::Clear()
{
  fevt->fMCP.fMulti = 0;
}

//________________________________________________
void HTMCP::InitTTreeBranch(TTree * theTree)
{
  theTree->Branch(Form("%s.",fName.c_str()),"HTMCPData",&(fevt->fMCP),32768,1);
  return;
}

//________________________________________________
void HTMCP::BuildEvent()
{
  HTMCPMap* map = (HTMCPMap*) fDetectorMapping;

  //Retrieving information from HTRootModule types
  for(int detNum = 0; detNum < fNumDetectors; detNum++)
  {

    //If the energy module exists for the anode
    if(map->GetEnergyModule(true, detNum) >= 0)
      fevt->fMCP.fEAnode[detNum] = ((HTRootCAEN7xx *)fModules[map->GetEnergyModule(true, detNum)])->
	GetData(map->GetEnergyChannel(true, detNum));
    else
      //std::cout << "Failed to find energy module for " << detNum << std::endl;
      fevt->fMCP.fEAnode[detNum] = -9999;

    //If the energy module exists for the back
    if(map->GetEnergyModule(false, detNum) >= 0)
      fevt->fMCP.fEBack[detNum] = ((HTRootCAEN7xx *)fModules[map->GetEnergyModule(false, detNum)])->
	GetData(map->GetEnergyChannel(false, detNum));
    else
      //std::cout << "Failed to find energy module for " << detNum << std::endl;
      fevt->fMCP.fEBack[detNum] = -9999;

    //If the time module exists get the time on anode
    if(map->GetTimeModule(true, detNum) >= 0)
      fevt->fMCP.fTimeAnode[detNum] = ((HTRootCAEN1x90 *)fModules[map->GetTimeModule(true, detNum)])->
	GetData(map->GetTimeChannel(true, detNum));
    else
      fevt->fMCP.fTimeAnode[detNum] = -9999;
    //If the time module exists get the time on anode
    if(map->GetTimeModule(false, detNum) >= 0)
      fevt->fMCP.fTimeBack[detNum] = ((HTRootCAEN1x90 *)fModules[map->GetTimeModule(false, detNum)])->
	GetData(map->GetTimeChannel(false, detNum));
    else
      fevt->fMCP.fTimeBack[detNum] = -9999;
    
    //Set the det num
    fevt->fMCP.fDetNum[detNum] = detNum;
      
  }//Loop over detector
  
  //Fill Root Event structure to be written on the tree
  FillMappedData();
  
  return;
}

//________________________________________________
void HTMCP::FillMappedData()
{
  fevt->fMCP.fMulti = fNumDetectors;

  return;
}
void HTMCP::InitMapping()
{
  fDetectorMapping = new HTMCPMap(fName, fNumDetectors);
}
