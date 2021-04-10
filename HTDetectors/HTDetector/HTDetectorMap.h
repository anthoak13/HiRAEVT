#ifndef HTDETECTORMAP_H
#define HTDETECTORMAP_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class HTDetectorMap {
public:
   HTDetectorMap(const std::string &); //! Constructor
   virtual ~HTDetectorMap();           //! Destructor

   virtual void Clear(); //! Clear mapping

   int LoadMapping(const char *); //! Loads detector mapping. Calls individual ParseAssignLine and ParseMapLine of the
                                  //! specific detector mappings
   int ParseAssignLine(
      const char *); //! Initializes module assignment order as it is defined within each individual detector
   virtual int ParseMapLine(const char *); //! Implemented in specific detector mappings

protected:
   std::string fName;
   std::map<std::string, int> *fModuleAssignmentOrder;
};

#endif
