#ifndef HTCALIBRATION_H
#define HTCALIBRATION_H

/* Class for handeling the calibration file 
 *
 * Exists as a singleton, that can be called by any calibratable detector.
 * This behavior needs to be supported in the detector class, 
 * Adam Anthony 7/31/2019
 */

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include <HTDetectorCalibration.h>
#include <HTExperimentInfo.h>
#include <HTExperimentalSetup.h>

class HTCalibration
{
public:
  static  HTCalibration* Instance();
  
  void ParseCalibrationFile();

  //Takes the type of detector that can be calibrated
  void AddCalibratableDetector(const std::string& name);

protected:
  HTCalibration();
  ~HTCalibration();

private:
  static HTCalibration *_instance;
  
  //List of valid detector types. Added to when a new detector is created.
  std::vector<std::string> validTypes;

  //Map of loaded calibrations 
  std::map<std::string, HTDetectorCalibration> calibrationMap;

  bool ParseDefineLine(std::string& line);
};



#endif /** #ifndef HTCALIBRATION_H **/
