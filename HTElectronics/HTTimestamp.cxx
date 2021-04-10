
#include "HTTimestamp.h"

#include <iostream>

using namespace std;

ClassImp(HTTimestamp);

//______________________________________________________________________________
HTTimestamp::HTTimestamp(const char *bName)
{
   // --
   //

   Clear();
   SetBranchName(bName);
}

//______________________________________________________________________________
void HTTimestamp::Clear(Option_t *option)
{
   // --
   //

   fTimestamp = 0;
}

//______________________________________________________________________________
void HTTimestamp::InitBranch(TTree *tree)
{
   // --
   //

   if (GetFillData()) {
      Char_t tmp[500];
      sprintf(tmp, "%s/L", GetBranchName());
      tree->Branch(GetBranchName(), &fTimestamp, tmp);
   } else {
      cout << "-->HTTimestamp::InitBranch  Branches will not be created or filled." << endl;
   }
}

//______________________________________________________________________________
Int_t HTTimestamp::Unpack(UShort_t *pEvent)
{
   // --
   //

   Clear();

   // skip the event header (exclusive size of event in units of 16-bit words)
   pEvent++;

   // The tstamp is the first 64-bits of the event, so recast the pointer
   // and dereference it to get the tstamp
   ULong64_t *timeStamp = reinterpret_cast<ULong64_t *>(pEvent);
   fTimestamp = *timeStamp;

   // done.
   return 4;
}
