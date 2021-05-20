#ifndef HTMUSICIC_H
#define HTMUSICIC_H

/* This detector describes the MUSIC ion chamber built for e12014
 * The notation of left and right on the triangle pads is from the beam's perspective
 *
 * Adam Anthony 5/7/2021
 *
 */

#include "HTDetector.h"

#include <utility>

#include "Math/Vector3D.h"

class HTMusicIC : public HTDetector {
private:
   Short_t fEnergyRaw[9]; // Raw energy in rectangle pads
   Double_t fEnergy[9];   // Calibrated energy in rectangle pads

   Double_t fTimeRaw[9]; // Raw time in rectangle pads
   Double_t fTime[9];    // Calibrated time in rectangle pads

   // The following are energy and position for the triangle pads
   Short_t fEnergyDSLeftRaw;
   Short_t fEnergyDSRightRaw;
   Short_t fEnergyUSLeftRaw;
   Short_t fEnergyUSRightRaw;

   Double_t fEnergyDSLeft;
   Double_t fEnergyDSRight;
   Double_t fEnergyUSLeft;
   Double_t fEnergyUSRight;

   Double_t fTimeDSLeftRaw;
   Double_t fTimeDSRightRaw;
   Double_t fTimeUSLeftRaw;
   Double_t fTimeUSRightRaw;

   Double_t fTimeDSLeft;
   Double_t fTimeDSRight;
   Double_t fTimeUSLeft;
   Double_t fTimeUSRight;

   Double_t fDriftVelocity; // Used to calculate the Y-position of the beam, mm/ns
   Double_t fTimeOffset;    // Used to calculate the y position of the beam, (think electronic offset)
   Double_t fReferenceTime; // Used to calculate the y-position of beam (think MCP anode time)

   // Positive values of offset move the origin further DS
   Double_t fOffsetZ; //! Offset from the center of the detector when calculating z position

public:
   HTMusicIC(const TString detectorName = "Undefined");
   virtual ~HTMusicIC();

   // Position functions
   ROOT::Math::XYZVector GetPositionUS();                 // Returns position of beam at triangle pads
   ROOT::Math::XYZVector GetPositionDS();                 // Returns position of beam at triangle pads
   ROOT::Math::XYZVector GetPosition(Double_t zPosition); // Position of beam at zPosition wrt offset

   // Setters
   void SetZOffset(Double_t offset) { fOffsetZ = offset; }
   void SetDriftVelocity(Double_t velocity) { fDriftVelocity = velocity; }
   void SetTimeOffset(Double_t offset) { fTimeOffset = offset; }
   void SetReferenceTime(Double_t refTime) { fReferenceTime = refTime; }
   
   void SetEnergyRaw(Int_t ch, Short_t energy);
   void SetTimeRaw(Int_t ch, Double_t time);

   void SetTimeDSRightRaw(Double_t time) { fTimeDSRightRaw = time; }
   void SetTimeDSLeftRaw(Double_t time) { fTimeDSLeftRaw = time; }
   void SetTimeUSRightRaw(Double_t time) { fTimeUSRightRaw = time; }
   void SetTimeUSLeftRaw(Double_t time) { fTimeUSLeftRaw = time; }

   void SetEnergyDSRightRaw(Short_t energy) { fEnergyDSRightRaw = energy; }
   void SetEnergyDSLeftRaw(Short_t energy) { fEnergyDSLeftRaw = energy; }
   void SetEnergyUSRightRaw(Short_t energy) { fEnergyUSRightRaw = energy; }
   void SetEnergyUSLeftRaw(Short_t energy) { fEnergyUSLeftRaw = energy; }

   // Getters
   Double_t GetZOffset() { return fOffsetZ; }
   Double_t GetDriftVelocity() { return fDriftVelocity; }
   Double_t GetTimeOffset() { return fTimeOffset; }
   
   Short_t GetEnergyRaw(Int_t ch);
   Double_t GetEnergy(Int_t ch);
   Double_t GetTimeRaw(Int_t ch);
   Double_t GetTime(Int_t ch);

   Double_t GetTimeDSRightRaw() { return fTimeDSRightRaw; }
   Double_t GetTimeDSLeftRaw() { return fTimeDSLeftRaw; }
   Double_t GetTimeUSRightRaw() { return fTimeUSRightRaw; }
   Double_t GetTimeUSLeftRaw() { return fTimeUSLeftRaw; }
   
   Double_t GetTimeDSRight() { return fTimeDSRight; }
   Double_t GetTimeDSLeft() { return fTimeDSLeft; }
   Double_t GetTimeUSRight() { return fTimeUSRight; }
   Double_t GetTimeUSLeft() { return fTimeUSLeft; }

   Short_t GetEnergyDSRightRaw() { return fEnergyDSRightRaw; }
   Short_t GetEnergyDSLeftRaw() { return fEnergyDSLeftRaw; }
   Short_t GetEnergyUSRightRaw() { return fEnergyUSRightRaw; }
   Short_t GetEnergyUSLeftRaw() { return fEnergyUSLeftRaw; }

   Double_t GetEnergyDSRight() { return fEnergyDSRight; }
   Double_t GetEnergyDSLeft() { return fEnergyDSLeft; }
   Double_t GetEnergyUSRight() { return fEnergyUSRight; }
   Double_t GetEnergyUSLeft() { return fEnergyUSLeft; }

   // Overrides
   virtual void Clear() override;
   virtual void Calibrate(const json &calibration) override;

   ClassDefOverride(HTMusicIC, 1)
};

#endif //#ifndef HTMUSICIC_H
