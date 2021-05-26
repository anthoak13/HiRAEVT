#ifndef HTTIMESTAMP_H
#define HTTIMESTAMP_H

/* This detector holds just a time and an energy (calibrated and raw)
 * Adam Anthony 5/6/202
 *
 */
#include "HTDetector.h"
#include "Rtypes.h"

class HTTimestamp : public HTDetector {

private:
   ULong64_t fTimestamp;

public:
   HTTimestamp(const TString detectorName = "Undefined");
   virtual ~HTTimestamp() {}

   // Getters
   ULong64_t GetTimestamp() const { return fTimestamp; }

   // Setters
   void SetTimestamp(ULong64_t timestamp) { fTimestamp = timestamp; }

   virtual void Clear() override;
   virtual void Calibrate(const json &calibration) override;

   ClassDefOverride(HTTimestamp, 1)
};

#endif //#ifndef HTTIMESTAMP_H
