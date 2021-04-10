#include "HTUSBStackMarker.h"

#include <iostream>

using namespace std;

ClassImp(HTUSBStackMarker);

HTUSBStackMarker::HTUSBStackMarker(UShort_t marker, const char *title)
{
   // --
   //

   SetTitle(title);
   SetGeo(-1);
   fMarker = marker;
}

Int_t HTUSBStackMarker::Unpack(vector<UShort_t> &event, Int_t offset)
{
   // --
   //

   Int_t markerOffset = offset;
   if (event[offset] == GetMarker())
      markerOffset++;
   else {
      cerr << "-->HTUSBStackMarker::Unpack  Event=" << event[offset] << " Offset=" << offset << " does not match "
           << GetMarker() << endl;
   }

   return markerOffset;
}