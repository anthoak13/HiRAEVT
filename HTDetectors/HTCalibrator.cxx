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

Double_t HTCalibrator::Calibrate(Double_t rawData, const json &calFragment) const
{
   // Get the method name and look for it
   TString methodName = calFragment["method"].get<std::string>();

   // Look for the method, and if found calibrate, otherwise throw an error
   if (methodName.EqualTo("poly"))
      return CalibratePolynomial(rawData, calFragment);

   throw std::invalid_argument(methodName.Append(" is not a valid method!"));
}

Double_t HTCalibrator::CalibratePolynomial(Double_t rawData, const std::vector<Double_t> &parameters) const
{
   Double_t calValue = 0;
   for (int i = 0; i < parameters.size(); ++i)
      calValue += TMath::Power(rawData, i) * parameters.at(i);

   return calValue;
}

Double_t HTCalibrator::CalibratePolynomial(Double_t rawData, const json &calFragment) const
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
