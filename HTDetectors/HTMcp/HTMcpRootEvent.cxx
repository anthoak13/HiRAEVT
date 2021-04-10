#include <HTMcpRootEvent.h>

//________________________________________________
HTMcpData::HTMcpData(int numDetectors) : fMulti(0)
{
   if (numDetectors > MAXNUMDET)
      throw std::invalid_argument(
         TString::Format("Tried to create %d detectors which is larger then the absolute cap of %d", numDetectors,
                         MAXNUMDET)
            .Data());

   fDetNum = new Int_t[numDetectors];

   fEAnode = new Short_t[numDetectors];
   fTimeAnode = new Double_t[numDetectors];

   fEBack = new Short_t[numDetectors];
   fTimeBack = new Double_t[numDetectors];
}

//________________________________________________
HTMcpData::~HTMcpData()
{
   delete[] fDetNum;

   delete[] fEAnode;
   delete[] fTimeAnode;

   delete[] fEBack;
   delete[] fTimeBack;
}

//________________________________________________
HTMcpRootEvent::HTMcpRootEvent(int numDetectors) : fMCP(numDetectors) {}

//________________________________________________
HTMcpRootEvent::~HTMcpRootEvent() {}

ClassImp(HTMcpData);
ClassImp(HTMcpRootEvent)
