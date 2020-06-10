#ifndef HTMCPROOTEVENT_H
#define HTMCPROOTEVENT_H


#include <TROOT.h>
#include <TString.h>

#include <stdexcept>


class HTMCPData
{
private:
  const static int  MAXNUMDET = 10;
public:
  Int_t    fMulti;
  Int_t    *fDetNum;    //[fMulti]
  Short_t  *fEAnode;    //[fMulti]
  Double_t *fTimeAnode; //[fMulti]

  Short_t  *fEBack;     //[fMulti]
  Double_t *fTimeBack;  //[fMulti]

  HTMCPData(int numDetectors = MAXNUMDET);
  virtual ~HTMCPData();

  ClassDef(HTMCPData,1);
};

class HTMCPRootEvent
{
public:
 HTMCPData fMCP;

 HTMCPRootEvent(int numDetectors);
 virtual ~HTMCPRootEvent();

 ClassDef(HTMCPRootEvent,1);
};

#endif
