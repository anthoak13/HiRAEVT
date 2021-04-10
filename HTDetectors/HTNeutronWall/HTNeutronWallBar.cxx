#include <HTNeutronWallBar.h>

//______________________________________________________________________________
// class constructor
HTNeutronWallBar::HTNeutronWallBar()
   : fAnoodeCommLeft(-9999), fAnodeIndLeft(-9999), fTimeLeft(-9999), fAnoodeCommRight(-9999), fAnodeIndRight(-9999),
     fTimeRight(-9999)
{
}

//______________________________________________________________________________
// destructor
HTNeutronWallBar::~HTNeutronWallBar() {}

//______________________________________________________________________________
void HTNeutronWallBar::SetAnodeCommonLeft(Short_t new_value)
{
   fAnoodeCommLeft = new_value;
}

//______________________________________________________________________________
void HTNeutronWallBar::SetAnodeIndividualLeft(Short_t new_value)
{
   fAnodeIndLeft = new_value;
}

//______________________________________________________________________________
void HTNeutronWallBar::SetTimeLeft(Double_t new_value)
{
   fTimeLeft = new_value;
}

//______________________________________________________________________________
void HTNeutronWallBar::SetAnodeCommonRight(Short_t new_value)
{
   fAnoodeCommRight = new_value;
}

//______________________________________________________________________________
void HTNeutronWallBar::SetAnodeIndividualRight(Short_t new_value)
{
   fAnodeIndRight = new_value;
}

//______________________________________________________________________________
void HTNeutronWallBar::SetTimeRight(Double_t new_value)
{
   fTimeRight = new_value;
}

//______________________________________________________________________________
Short_t HTNeutronWallBar::GetAnodeCommonLeft() const
{
   return fAnoodeCommLeft;
}

//______________________________________________________________________________
Short_t HTNeutronWallBar::GetAnodeIndividualLeft() const
{
   return fAnodeIndLeft;
}

//______________________________________________________________________________
Double_t HTNeutronWallBar::GetTimeLeft() const
{
   return fTimeLeft;
}

//______________________________________________________________________________
Short_t HTNeutronWallBar::GetAnodeCommonRight() const
{
   return fAnoodeCommRight;
}

//______________________________________________________________________________
Short_t HTNeutronWallBar::GetAnodeIndividualRight() const
{
   return fAnodeIndRight;
}

//______________________________________________________________________________
Double_t HTNeutronWallBar::GetTimeRight() const
{
   return fTimeRight;
}

//______________________________________________________________________________
Short_t *HTNeutronWallBar::GetAnodeCommonLeftPointer()
{
   return &fAnoodeCommLeft;
}

//______________________________________________________________________________
Short_t *HTNeutronWallBar::GetAnodeIndividualLeftPointer()
{
   return &fAnodeIndLeft;
}

//______________________________________________________________________________
Double_t *HTNeutronWallBar::GetTimeLeftPointer()
{
   return &fTimeLeft;
}

//______________________________________________________________________________
Short_t *HTNeutronWallBar::GetAnodeCommonRightPointer()
{
   return &fAnoodeCommRight;
}

//______________________________________________________________________________
Short_t *HTNeutronWallBar::GetAnodeIndividualRightPointer()
{
   return &fAnodeIndRight;
}

//______________________________________________________________________________
Double_t *HTNeutronWallBar::GetTimeRightPointer()
{
   return &fTimeRight;
}

//______________________________________________________________________________
void HTNeutronWallBar::Clear()
{
   fAnoodeCommLeft = -9999;
   fAnodeIndLeft = -9999;
   fTimeLeft = -9999;
   fAnoodeCommRight = -9999;
   fAnodeIndRight = -9999;
   fTimeRight = -9999;

   return;
}
