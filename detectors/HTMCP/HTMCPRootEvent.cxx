#include <HTMCPRootEvent.h>

ClassImp(HTMCPData)
ClassImp(HTMCPRootEvent)

//________________________________________________
HTMCPData::HTMCPData(int numDetectors) : fMulti(0)
{
  fDetNum    = new Int_t[numDetectors];
  
  fEAnode    = new Short_t[numDetectors];
  fTimeAnode = new Double_t[numDetectors];

  fEBack     = new Short_t[numDetectors];
  fTimeBack  = new Double_t[numDetectors];

}

//________________________________________________
HTMCPData::~HTMCPData()
{
  delete [] fDetNum;
  
  delete [] fEAnode;
  delete [] fTimeAnode;

  delete [] fEBack;
  delete [] fTimeBack;
}

//________________________________________________
HTMCPRootEvent::HTMCPRootEvent(int numDetectors) :
fMCP(numDetectors)
{
}

//________________________________________________
HTMCPRootEvent::~HTMCPRootEvent()
{
}
