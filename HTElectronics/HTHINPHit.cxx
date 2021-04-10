#include "HTHINPHit.h"

// WARNING: the maximum number of hits in hinp is for now set at 1000
static const int NMAXHITS = 1000;
////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
HTHINPHit::HTHINPHit() : fNHits(0)
{
   fBank = new UShort_t[NMAXHITS];
   fXLMIndex = new UShort_t[NMAXHITS];
   fChip = new UShort_t[NMAXHITS];
   fChannel = new UShort_t[NMAXHITS];
   fChMismatch = new Bool_t[NMAXHITS];
   fEnergyHi = new UShort_t[NMAXHITS];
   fEnergyLo = new UShort_t[NMAXHITS];
   fTime = new UShort_t[NMAXHITS];
}

//______________________________________________________________________________
HTHINPHit::~HTHINPHit()
{
   delete[] fBank;
   delete[] fXLMIndex;
   delete[] fChip;
   delete[] fChannel;
   delete[] fChMismatch;
   delete[] fEnergyHi;
   delete[] fEnergyLo;
   delete[] fTime;
}
