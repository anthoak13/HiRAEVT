#include <iostream>

#include "RBUSBStackMarker.h"

using namespace std;

ClassImp(RBUSBStackMarker);

RBUSBStackMarker::RBUSBStackMarker(UShort_t marker, const char *title)
{
  // --
  //
  
  SetTitle(title);
  SetGeo(-1);
  fMarker = marker;
}


Int_t RBUSBStackMarker::Unpack(vector<UShort_t>& event, Int_t offset)
{
  // --
  //
  
  Int_t markerOffset = offset;
  if(event[offset] == GetMarker()) markerOffset++;
  else{
    cerr << "-->RBUSBStackMarker::Unpack  Event="
         << event[offset] << " Offset=" << offset
         << " does not match " << GetMarker() <<endl;
  }
  
  return markerOffset;
}