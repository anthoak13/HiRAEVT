// Implementation for HTDetectorMapper
#include "HTDetectorMapper.h"

#include <fstream>
#include <iostream>

HTDetectorMapper::HTDetectorMapper(const json &config) : fConfiguration(config)
{
   // Get the calibration info if it is in the config file
   if (fConfiguration.contains("calibration"))
      fCalibration = fConfiguration["calibration"];

   // if no calibration field, then look for a calibration file
   else if (fConfiguration.contains("calibrationFile")) {
      // Load calibrationFile if we can open it
      TString calFileName = fConfiguration["calibrationFile"].get<std::string>();
      std::ifstream calFile(calFileName);

      if (!calFile)
         std::cout << "Failed to open config file " << calFileName << std::endl;
      else
         calFile >> fCalibration;

   } else // No calibration data found
      std::cout << "No calibration data found." << std::endl;
}
