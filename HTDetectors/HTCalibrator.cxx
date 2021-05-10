/* Implementation of singleton for calibrating data
 * Adam Anthony 5/6/2021
 */

#include "HTCalibrator.h"

#include "TMath.h"
#include "TString.h"

#include <string>

#include "nlohmann/json.hpp"

HTCalibrator *HTCalibrator::fInstance = nullptr;

const HTCalibrator *HTCalibrator::Instance()
{
   if (fInstance == nullptr)
      fInstance = new HTCalibrator();
   return fInstance;
}

Double_t HTCalibrator::Calibrate(Double_t rawData, const json &calFragment)
{
   // Get the method name and look for it
   TString methodName = calFragment["method"].get<std::string>();

   // Look for the method, and if found calibrate, otherwise throw an error
   if (methodName.EqualTo("poly"))
      return CalibratePolynomial(rawData, calFragment);

   if (methodName.EqualTo("copy"))
      return rawData;

   throw std::invalid_argument(methodName.Append(" is not a valid method!"));
}

Double_t HTCalibrator::TimeWalkOffset(Double_t rawEnergy, const std::vector<Double_t> &parameters)
{
   if (parameters.size() != 3)
      throw std::invalid_argument(TString::Format(
         "Parameter list passed for TimeWalkOffset had %lu parameters. Expected 3!", parameters.size()));

   // Now get the offset
   return parameters[0] / TMath::Sqrt(rawEnergy) + parameters[1] * rawEnergy + parameters[2];
}

Double_t HTCalibrator::TimeWalkOffset(Double_t rawEnergy, const json &calFragment)
{
   // Verify the method actually is poly
   std::string methodName = calFragment["method"];
   if (methodName != "walkCorrection")
      throw std::invalid_argument(methodName.append(" is not walkCorrection!"));

   // Get the parameter list and pass it on
   std::vector<Double_t> paramList;
   for (double param : calFragment["parameters"])
      paramList.push_back(param);
   return TimeWalkOffset(rawEnergy, paramList);
}

Double_t HTCalibrator::CalibratePolynomial(Double_t rawData, const std::vector<Double_t> &parameters)
{
   Double_t calValue = 0;
   for (int i = 0; i < parameters.size(); ++i)
      calValue += TMath::Power(rawData, i) * parameters.at(i);

   return calValue;
}

Double_t HTCalibrator::CalibratePolynomial(Double_t rawData, const json &calFragment)
{
   // Verify the method actually is poly
   std::string methodName = calFragment["method"];
   if (methodName != "poly")
      throw std::invalid_argument(methodName.append(" is not poly!"));

   // Get the parameter list and pass it on
   std::vector<Double_t> paramList;
   for (double param : calFragment["parameters"])
      paramList.push_back(param);

   return CalibratePolynomial(rawData, paramList);
}
