#ifndef HTMCP_H
#define HTMCP_H

/* This detector represents one of the ExB MCP detectors build for e12014 PID system
 * It records the energy and time at the back of the MCP and the Anode.
 *
 * Adam Anthony 5/6/2021
 *
 */

#include "HTDetector.h"

using vecDouble = std::vector<Double_t>;

class HTMcp : public HTDetector {

private:
   Short_t fEnergyMcpRaw;
   Short_t fEnergyAnodeRaw;
   Double_t fEnergyMcp;
   Double_t fEnergyAnode;

   vecDouble fTimeMcpRaw;
   vecDouble fTimeAnodeRaw;
   vecDouble fTimeMcp;
   vecDouble fTimeAnode;

public:
   HTMcp(const TString detectorName = "Undefined");
   virtual ~HTMcp();

   // Getters
   Short_t GetEnergyMcpRaw() { return fEnergyMcpRaw; }
   Short_t GetEnergyAnodeRaw() { return fEnergyAnodeRaw; }
   Double_t GetEnergyMcp() { return fEnergyMcp; }
   Double_t GetEnergyAnode() { return fEnergyAnode; }

   const vecDouble &GetTimeMcpRaw() { return fTimeMcpRaw; }
   const vecDouble &GetTimeAnodeRaw() { return fTimeAnodeRaw; }
   const vecDouble &GetTimeMcp() { return fTimeMcp; }
   const vecDouble &GetTimeAnode() { return fTimeAnode; }

   // Setters
   void SetEnergyMcpRaw(Short_t energy);
   void SetEnergyAnodeRaw(Short_t energy);
   void SetTimeMcpRaw(const vecDouble &time);
   void SetTimeAnodeRaw(const vecDouble &time);

   virtual void Clear() override;
   virtual void Calibrate(const json &calibration) override;

   ClassDefOverride(HTMcp, 1)
};

#endif //#ifndef HTMCP_H
