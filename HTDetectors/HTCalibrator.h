#ifndef HTCALIBRATOR_H
#define HTCALIBRATOR_H

/* This is a singeltont that functions as a calibration helper for
 * the detectors. It supports polynomial calibration, but can be extended for
 * additional calibration methods.
 * Adam Anthony 5/6/2021
 *
 * Calibration methods (name: parameters)
 * poly: takes an array of doubles
 */

#include "Rtypes.h"

#include <vector>

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

class HTCalibrator {
private:
   static HTCalibrator *fInstance;

public:
   const static HTCalibrator *Instance();

   // returns Sum (rawData^i * parameters_i)
   Double_t CalibratePolynomial(Double_t rawData, const std::vector<Double_t> &parameters) const;

   // calFragment should be a calibration object { "method":methodName, "parameters":[parArray]}
   Double_t CalibratePolynomial(Double_t rawData, const json &calFragment) const;

   // calFragment should be a calibration object { "method":methodName, "parameters":[parArray]}
   // will through an error if bad data is passed
   Double_t Calibrate(Double_t rawData, const json &calFragment) const;
};

#endif //#ifndef HTCALIBRATOR_H
