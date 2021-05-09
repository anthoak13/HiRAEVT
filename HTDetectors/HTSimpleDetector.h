#ifndef HTSIMPLEDETECTOR_H
#define HTSIMPLEDETECTOR_H

/* This detector holds just a time and an energy (calibrated and raw)
 * Adam Anthony 5/6/202
 *
 */
#include "HTDetector.h"
#include "Rtypes.h"

class HTSimpleDetector : public HTDetector {

private:
   Short_t fEnergyRaw;
   Double_t fTimeRaw;

   Double_t fEnergy;
   Double_t fTime;

public:
   HTSimpleDetector(const TString detectorName = "Undefined");
   virtual ~HTSimpleDetector();

   // Getters
   Short_t GetEnergyRaw() const { return fEnergyRaw; }
   Double_t GetTimeRaw() const { return fTimeRaw; }
   Double_t GetEnergy() const { return fEnergy; }
   Double_t GetTime() const { return fTime; }

   // Setters
   void SetEnergyRaw(Short_t energyRaw);
   void SetTimeRaw(Double_t timeRaw);

   virtual void Clear() override;
   virtual void Calibrate(const json &calibration) override;

   ClassDefOverride(HTSimpleDetector, 2)
};

#endif //#ifndef HTSIMPLEDETECTOR_H
