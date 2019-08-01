/* Implementation of HTCalibration */
#include "HTCalibration.h"

HTCalibration* HTCalibration::_instance = nullptr;
HTCalibration* HTCalibration::Instance()
{
  if(_instance == nullptr)
    _instance = new HTCalibration();
  return _instance;
}

void HTCalibration::ParseCalibrationFile()
{
  //Try to open the calibration file
  std::ifstream fileIn(
    HTExperimentInfo::Instance()->GetRunInfo()->GetCalibrationFile());

  if(!fileIn.is_open())
  {
    std::cout << "No calibration file to open: "
	      << HTExperimentInfo::Instance()->GetRunInfo()->GetCalibrationFile()
	      << std::endl;
    return;
  }

  while(!fileIn.eof())
  {
    std::string lineIn;
    std::getline(fileIn, lineIn);
    lineIn = std::string(lineIn.substr(0,lineIn.find("*")));
    if(!lineIn.empty())
      std::cout << lineIn << std::endl;

    //If it is a define line create a calibration file
    if(lineIn.find("define ") != std::string::npos)
      ParseDefineLine(lineIn);
    
  }
  
  //Try to open the file
}

bool HTCalibration::ParseDefineLine(std::string& line)
{
  std::string define, type, name;

  std::istringstream sstream(line);
  sstream >> define >> type >> name;
  std::cout << "Looking for detector: " << name << std::endl;

  auto detIt = HTExperimentalSetup::Instance()->GetDetectors()->find(name);
  if(detIt  == HTExperimentalSetup::Instance()->GetDetectors()->end())
    return false;
  
  detIt->second->InitCalibration();
  return true;
  
}
HTCalibration::HTCalibration()
{
}
HTCalibration::~HTCalibration()
{
}
