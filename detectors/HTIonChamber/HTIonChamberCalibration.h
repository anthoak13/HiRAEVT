#ifndef HTIONCHAMBERCALIBRATION_H
#define HTIONCHAMBERCALIBRATION_H
/* Class to hold detector calibrations
 * 
 * These classes are stored in a map in HTCalibration
 * Adam Anthony 7/31/2019
 */

#include "HTDetectorCalibration.h"
#include <vector>

//[detNum][c_i]
using CaliPolynomial = std::vector<std::vector<double>>;

class HTIonChamberCalibration : public HTDetectorCalibration
{
public:
  void ParseCalibrationLine();
  void ParsePedestalLine();

  float Calibrate(int detNum, int rawCh);

private:
  CaliPolynomial calPoly;

};
#endif /* #ifndef HTIONCHAMBERCALIBRATION_H */
