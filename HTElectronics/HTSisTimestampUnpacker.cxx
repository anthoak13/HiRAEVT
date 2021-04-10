//
//  HTSisTimestampUnpacker.cpp
//

//#include <config.h>
#include "HTSisTimestampUnpacker.h"
//#include <Event.h>
//#include <stdint.h>
#include <iostream>
#include <stdint.h>

using namespace std;

ClassImp(HTSisTimestampUnpacker)

   using std::vector;
using std::string;

/////////////////////////////////////////////////////////////////////
// Canonicals..

/*!
 Construction is a no-op.

 */
HTSisTimestampUnpacker::HTSisTimestampUnpacker(const char *chName)
{

   Clear();
   SetBranchName(chName);
}

/*!
 Destruction is a no-op.
 */
HTSisTimestampUnpacker::~HTSisTimestampUnpacker() {}

void HTSisTimestampUnpacker::InitBranch(TTree *tree)
{

   if (GetFillData()) {
      tree->Branch(GetBranchName(), fTimestamp, TString::Format("%s[2]/l", GetBranchName()));
   } else {
      cout << "HTSisTimestamp InitBranch problem" << endl;
   }
}

void HTSisTimestampUnpacker::Clear()
{

   fTimestamp[0] = 0;
   fTimestamp[1] = 0;
}

Int_t HTSisTimestampUnpacker::Unpack(vector<UShort_t> &event, UInt_t offset)
{
   Clear();

   uint64_t low0 = event[offset];
   uint64_t mid0 = event[offset + 1];
   uint64_t low1 = event[offset + 2];
   uint64_t mid1 = event[offset + 3];
   uint64_t high0 = event[offset + 4];
   uint64_t high1 = event[offset + 5];
   offset += 6;

   fTimestamp[0] = low0 | (mid0 << 16) | (high0 << 32);
   fTimestamp[1] = low1 | (mid1 << 16) | (high1 << 32);

   return offset;
}
