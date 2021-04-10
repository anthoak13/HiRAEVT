#include <HTVetoWallArray.h>

//______________________________________________________________________________
HTVetoWallArray::HTVetoWallArray(int num_bars) : fVWArray(0), fNumBars(num_bars)
{
   fVWArray = (HTVetoWallBar **)new HTVetoWallBar *[fNumBars];
   for (int i = 0; i < fNumBars; i++) {
      fVWArray[i] = (HTVetoWallBar *)new HTVetoWallBar;
   }
}

//______________________________________________________________________________
HTVetoWallArray::~HTVetoWallArray()
{
   if (!fVWArray)
      return;
   for (int i = 0; i < fNumBars; i++) {
      if (fVWArray[i])
         delete fVWArray[i];
   }
   if (fVWArray)
      delete[] fVWArray;
}

//______________________________________________________________________________
HTVetoWallBar *HTVetoWallArray::GetBar(Int_t bar_number) const
{
   return fVWArray[bar_number];
}

//______________________________________________________________________________
Int_t HTVetoWallArray::GetNumberBars() const
{
   return fNumBars;
}

//______________________________________________________________________________
void HTVetoWallArray::Clear()
{
   for (int i = 0; i < fNumBars; i++) {
      fVWArray[i]->Clear();
   }
}
