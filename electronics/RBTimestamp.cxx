
#include <iostream>

#include "RBTimestamp.h"

using namespace std;

ClassImp(RBTimestamp);

//______________________________________________________________________________
RBTimestamp::RBTimestamp(const char *bName)
{
  // --
  //
  
  Clear();
  SetBranchName(bName);
}


//______________________________________________________________________________
void RBTimestamp::Clear(Option_t *option)
{
  // --
  //
  
  fTimestamp = 0;
}

//______________________________________________________________________________
void RBTimestamp::InitBranch(TTree *tree)
{
  // --
  //
  
  if(GetFillData()){
    Char_t tmp[500];
    sprintf(tmp,"%s/l",GetBranchName());
    tree->Branch(GetBranchName(), &fTimestamp, tmp);
  }else{
    cout << "-->RBTimestamp::InitBranch  Branches will not be created or filled." << endl;
  }
}

//______________________________________________________________________________
Int_t RBTimestamp::Unpack(UShort_t *pEvent)
{
  // --
  //
  
  Clear();
  
  // skip the event header (exclusive size of event in units of 16-bit words)
  pEvent++;
  
  // The tstamp is the first 64-bits of the event, so recast the pointer
  // and dereference it to get the tstamp
  ULong64_t *timeStamp = reinterpret_cast<ULong64_t*>(pEvent);
  fTimestamp = *timeStamp;
  
  // done.
  return 4;
}





