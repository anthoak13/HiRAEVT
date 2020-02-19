#include <HTSisTimestampMap.h>

//________________________________________________
HTSisTimestampMap::HTSisTimestampMap(const std::string& name, int num_detectors) :
  HTDetectorMap(name),
  fNumDetectors(num_detectors)
{
  fTimestampModule  = new int[fNumDetectors];
  fTimestampChannel = new int[fNumDetectors];

  Clear();
}

//________________________________________________
HTSisTimestampMap::~HTSisTimestampMap()
{}


void HTSisTimestampMap::Clear()
{
  fModuleAssignmentOrder->clear();
  
  for(int i=0; i < fNumDetectors; ++i)
  {
    fTimestampModule[i]  = -1;
    fTimestampChannel[i] = -1;
  }
}

//________________________________________________
int HTSisTimestampMap::ParseMapLine(const char * line_to_parse)
{
  //String has the format "map DetName ChType DetNum ModuleName ModuleChannel"
  
  //This is a map string so create a stream to read it
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));

  std::string DetectorName, ChType, ModuleName;
  int detNumber, moduleNumber, moduleCh;
  
  //Load in all of the info
  LineStream >> DetectorName >> ChType >> detNumber >> ModuleName >> moduleCh;

  // Make sure this is the right detector
  if(DetectorName.compare(fName)!=0) return 0;

  //Get the module number from the map
  moduleNumber = fModuleAssignmentOrder->at(ModuleName);

  if(ChType.compare("TIMESTAMP") == 0)
  {
    fTimestampModule[detNumber] = moduleNumber;
    fTimestampChannel[detNumber]= moduleCh;
  }
  return 1;
}
