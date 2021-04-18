/* *******************************************************************************************************
 * HTVetoWallBar Class
 * simple Veto Wall scintillator bar derived from HTVVbar class
 * implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * 04/29/2018 v1.0
 *
 * ********************************************************************************************************/

#ifndef HTVETOWALLBAR_H
#define HTVETOWALLBAR_H

#include <TROOT.h>

class HTVetoWallBar {
private:
   // rawdata
   Int_t fAnoodeCommTop;
   Double_t fTimeTop;
   Int_t fAnoodeCommBottom;
   Double_t fTimeBottom;

public:
   HTVetoWallBar();  // constructor
   ~HTVetoWallBar(); // destructor

   // Setting methods
   void SetAnodeCommonTop(Int_t);
   void SetTimeTop(Double_t);
   void SetAnodeCommonBottom(Int_t);
   void SetTimeBottom(Double_t);

   // Getting methods
   Int_t GetAnodeCommonTop() const;    // Anode common signal Top (channels)
   Double_t GetTimeTop() const;        // Time signal Top (channels)
   Int_t GetAnodeCommonBottom() const; // Anode common signal Bottom (channels)
   Double_t GetTimeBottom() const;     // Time signal Bottom (channels)

   // Getting methods pointers
   Int_t *GetAnodeCommonTopPointer();    // Anode common signal Top (channels)
   Double_t *GetTimeTopPointer();        // Time signal Top (channels)
   Int_t *GetAnodeCommonBottomPointer(); // Anode common signal Bottom (channels)
   Double_t *GetTimeBottomPointer();     // Time signal Bottom (channels)

   void Clear();
};

#endif
