#ifndef HTDETECTORCALIBRATION_H
#define HTDETECTORCALIBRATION_H
/* Class to hold detector calibrations
 * 
 * These classes are stored in a map in HTCalibration
 * Adam Anthony 7/31/2019
 */


class HTDetectorCalibration
{
public:
  virtual void ParseCalibrationLine() =0;
  virtual void ParsePedestalLine();

};
#endif /* #ifndef HTDETECTORCALIBRATION_H */
