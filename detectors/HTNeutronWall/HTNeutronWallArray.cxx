#include <HTNeutronWallArray.h>

//______________________________________________________________________________
HTNeutronWallArray::HTNeutronWallArray(int num_bars) :
fNWArray(0),
fNumBars(num_bars)
{
  fNWArray  = (HTNeutronWallBar **) new HTNeutronWallBar * [fNumBars];
  for (int i=0; i<fNumBars; i++) {
    fNWArray[i] = (HTNeutronWallBar *) new HTNeutronWallBar;
  }
}

//______________________________________________________________________________
HTNeutronWallArray::~HTNeutronWallArray()
{
  if(!fNWArray) return;
  for(int i=0; i<fNumBars; i++) {
    if(fNWArray[i]) delete fNWArray[i];
  }
  if(fNWArray) delete [] fNWArray;
}

//______________________________________________________________________________
HTNeutronWallBar * HTNeutronWallArray::GetBar(Int_t bar_number) const
{
  return fNWArray[bar_number];
}

//______________________________________________________________________________
Int_t HTNeutronWallArray::GetNumberBars() const
{
  return fNumBars;
}

//______________________________________________________________________________
void HTNeutronWallArray::Clear()
{
  for (int i=0; i<fNumBars; i++)  {
    fNWArray[i]->Clear();
  }
}
