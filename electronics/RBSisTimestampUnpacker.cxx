//
//  RBSisTimestampUnpacker.cpp
//

//#include <config.h>
#include "RBSisTimestampUnpacker.h"
//#include <Event.h>
//#include <stdint.h>
#include <iostream>
#include <stdint.h>

using namespace std;

ClassImp(RBSisTimestampUnpacker)

using std::vector;
using std::string;


/////////////////////////////////////////////////////////////////////
// Canonicals..

/*!
 Construction is a no-op.

 */
RBSisTimestampUnpacker::RBSisTimestampUnpacker(const char* chName){

  Clear();
  SetBranchName(chName);

}

/*!
 Destruction is a no-op.
 */
RBSisTimestampUnpacker::~RBSisTimestampUnpacker() {}



void RBSisTimestampUnpacker::InitBranch(TTree* tree)
{

  if (GetFillData()){
    Char_t tmp[500];
    sprintf(tmp,"%s/L",GetBranchName());
    std::string KoreanElectronics(GetBranchName());
    KoreanElectronics += "Koreans";
    tree->Branch(KoreanElectronics.c_str(), &fTimestampKoreans, (KoreanElectronics + "/L").c_str());
    tree->Branch(GetBranchName(), &fTimestamp, tmp);
}else{
    cout << "RBSisTimestamp InitBranch problem" << endl;
  }

}

void RBSisTimestampUnpacker::Clear()
{

  fTimestamp = 0;
  fTimestampKoreans = 0;
}


Int_t RBSisTimestampUnpacker::Unpack(vector<UShort_t>& event, UInt_t offset)
{
  Clear();

  uint16_t low0 =event[offset];
  uint16_t mid0 =event[offset+1];
  uint16_t low1 =event[offset+2];
  uint16_t mid1 =event[offset+3];
  uint16_t high0 =event[offset+4];
  uint16_t high1 =event[offset+5];
  offset += 6;

  uint64_t high = high1;
  uint64_t timestamp = low1 | (mid1 << 16) | (high << 32);
  high =high0;
  uint64_t timestampKoreans = low0 | (mid0 << 16) | (high << 32);
  fTimestamp = timestamp;
  fTimestampKoreans = timestampKoreans;

  return offset;

}
