#include <HTDetectorMap.h>
#include <string>
//________________________________________________
HTDetectorMap::HTDetectorMap(json mappingJSON)
{
   fName = (std::string)mappingJSON["DetName"];
}

//________________________________________________
HTDetectorMap::~HTDetectorMap()
{
}
