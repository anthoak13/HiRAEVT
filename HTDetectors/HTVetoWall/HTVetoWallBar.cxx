#include <HTVetoWallBar.h>

//______________________________________________________________________________
// class constructor
HTVetoWallBar::HTVetoWallBar() : fAnoodeCommTop(-9999), fTimeTop(-9999), fAnoodeCommBottom(-9999), fTimeBottom(-9999) {}

//______________________________________________________________________________
// destructor
HTVetoWallBar::~HTVetoWallBar() {}

//______________________________________________________________________________
void HTVetoWallBar::SetAnodeCommonTop(Int_t new_value)
{
   fAnoodeCommTop = new_value;
}

//______________________________________________________________________________
void HTVetoWallBar::SetTimeTop(Double_t new_value)
{
   fTimeTop = new_value;
}

//______________________________________________________________________________
void HTVetoWallBar::SetAnodeCommonBottom(Int_t new_value)
{
   fAnoodeCommBottom = new_value;
}

//______________________________________________________________________________
void HTVetoWallBar::SetTimeBottom(Double_t new_value)
{
   fTimeBottom = new_value;
}

//______________________________________________________________________________
Int_t HTVetoWallBar::GetAnodeCommonTop() const
{
   return fAnoodeCommTop;
}

//______________________________________________________________________________
Double_t HTVetoWallBar::GetTimeTop() const
{
   return fTimeTop;
}

//______________________________________________________________________________
Int_t HTVetoWallBar::GetAnodeCommonBottom() const
{
   return fAnoodeCommBottom;
}

//______________________________________________________________________________
Double_t HTVetoWallBar::GetTimeBottom() const
{
   return fTimeBottom;
}

//______________________________________________________________________________
Int_t *HTVetoWallBar::GetAnodeCommonTopPointer()
{
   return &fAnoodeCommTop;
}

//______________________________________________________________________________
Double_t *HTVetoWallBar::GetTimeTopPointer()
{
   return &fTimeTop;
}

//______________________________________________________________________________
Int_t *HTVetoWallBar::GetAnodeCommonBottomPointer()
{
   return &fAnoodeCommBottom;
}

//______________________________________________________________________________
Double_t *HTVetoWallBar::GetTimeBottomPointer()
{
   return &fTimeBottom;
}

//______________________________________________________________________________
void HTVetoWallBar::Clear()
{
   fAnoodeCommTop = -9999;
   fTimeTop = -9999;
   fAnoodeCommBottom = -9999;
   fTimeBottom = -9999;

   return;
}
