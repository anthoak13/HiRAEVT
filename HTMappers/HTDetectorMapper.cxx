// Implementation for HTDetectorMapper
#include "HTDetectorMapper.h"

#include "HTMapper.h"

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
         std::cout << "\tFailed to open calibration file " << calFileName << std::endl;
      else {
         std::cout << "\tLoading calibration file: " << calFileName << std::endl;
         calFile >> fCalibration;
      }
   } else // No calibration data found
   {
      std::cout << "\tNo calibration data found for " << fConfiguration["detectorName"] << std::endl;
      return;
   }

   // Now look to see if there is a calibrationList. If there is, then loop through and look for
   // a matching run. If there is no run specified it is used as a default
   if (!fCalibration.contains("calibrationList"))
      return;

   // Loop through and look for an exact match to a run
   for (const auto &info : fCalibration["calibrationList"])
      if (info.value("run", -1) == HTMapper::Instance()->GetRunNumber()) {
         fCalibration = info;
         std::cout << "\tUsing calibration for run " << info["run"] << std::endl;
         return;
      }

   // Loop through and look for a range
   for (const auto &info : fCalibration["calibrationList"])
      if (info.contains("runRange"))
         if (info["runRange"][0] <= HTMapper::Instance()->GetRunNumber() &&
             info["runRange"][1] >= HTMapper::Instance()->GetRunNumber()) {
            // For some reason this cout needs to be before the assignment or it errors
            std::cout << "\tUsing calibration for range " << info["runRange"] << std::endl;
            fCalibration = info;
            return;
         }

   // Loop through and look for a default mapping
   for (const auto &info : fCalibration["calibrationList"])
      if (info.contains("run") || info.contains("runRange"))
         continue;
      else {
         fCalibration = info;
         std::cout << "\tUsing default calibration" << std::endl;
         return;
      }
}
