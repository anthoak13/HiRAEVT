#ifndef HTDETECTORMAP_H
#define HTDETECTORMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

class HTDetectorMap
{
public :
  HTDetectorMap(const char *);                       //!Constructor
  virtual ~HTDetectorMap();                          //!Destructor

  int LoadMapping(const char *);                     //!Loads detector mapping. Calls individual ParseAssignLine and ParseMapLine of the specific detector mappings
  int ParseAssignLine(const char *);                 //!Initializes module assignment order as it is defined within each individual detector
  virtual int ParseMapLine(const char *);            //!Implemented in specific detector mappings

protected :
  std::string fName;
  std::map<std::string, int> * fModuleAssignmentOrder;

};

#endif
