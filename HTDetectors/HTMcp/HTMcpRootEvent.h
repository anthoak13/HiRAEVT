#ifndef HTMCPROOTEVENT_H
#define HTMCPROOTEVENT_H

#include <TROOT.h>
#include <TString.h>
#include <stdexcept>

class HTMcpData {
private:
   const static int MAXNUMDET = 10;

public:
   Int_t fMulti;
   Int_t *fDetNum;       //[fMulti]
   Short_t *fEAnode;     //[fMulti]
   Double_t *fTimeAnode; //[fMulti]

   Short_t *fEBack;     //[fMulti]
   Double_t *fTimeBack; //[fMulti]

   HTMcpData(int numDetectors = MAXNUMDET);
   virtual ~HTMcpData();

   ClassDef(HTMcpData, 1);
};

class HTMcpRootEvent {
public:
   HTMcpData fMCP;

   HTMcpRootEvent(int numDetectors);
   virtual ~HTMcpRootEvent();

   ClassDef(HTMcpRootEvent, 1);
};

#endif
