#include <HTMcpMap.h>

//________________________________________________
HTMcpMap::HTMcpMap(const std::string &name, int num_detectors) : HTDetectorMap(name), fNumDetectors(num_detectors)
{
   fEnergyModule = new int *[2];
   fEnergyChannel = new int *[2];
   fTimeModule = new int *[2];
   fTimeChannel = new int *[2];

   for (int i = 0; i < 2; ++i) {
      fEnergyModule[i] = new int[fNumDetectors];
      fEnergyChannel[i] = new int[fNumDetectors];
      fTimeModule[i] = new int[fNumDetectors];
      fTimeChannel[i] = new int[fNumDetectors];
   }
   Clear();
}

//________________________________________________
HTMcpMap::~HTMcpMap()
{
   for (int j = 0; j < 2; ++j) {
      if (fEnergyModule[j])
         delete[] fEnergyModule[j];
      if (fEnergyChannel[j])
         delete[] fEnergyChannel[j];
      if (fTimeModule[j])
         delete[] fTimeModule[j];
      if (fTimeChannel[j])
         delete[] fTimeChannel[j];
   }
   delete[] fEnergyModule;
   delete[] fEnergyChannel;
   delete[] fTimeModule;
   delete[] fTimeChannel;
}

//________________________________________________
void HTMcpMap::Clear()
{
   fModuleAssignmentOrder->clear();
   for (int j = 0; j < 2; ++j)
      for (int i = 0; i < fNumDetectors; i++) {
         fEnergyModule[j][i] = -1;
         fEnergyChannel[j][i] = -1;
         fTimeModule[j][i] = -1;
         fTimeChannel[j][i] = -1;
      }
}

// String has the format "map DetectorName anodeType ChType DetectorNumber ModuleName ModuleNumber"
int HTMcpMap::ParseMapLine(const char *line_to_parse)
{
   // This is a map string so create a stream to read it
   std::string LineReadCommentLess(line_to_parse);
   std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ") + 4));

   // std::cout << "Processing: " <<  LineReadCommentLess << std::endl;

   std::string detectorName, anodeType, chType, moduleName;
   int detNumber, moduleNumber, moduleCh;

   // Load in all of the info
   LineStream >> detectorName >> anodeType >> chType >> detNumber >> moduleName >> moduleCh;

   // Make sure this is the right detector
   if (detectorName.compare(fName) != 0)
      return 0;

   // Get the module number from the map
   moduleNumber = fModuleAssignmentOrder->at(moduleName);

   // Get if anode or back
   bool anode;
   if (anodeType.compare("ANODE") == 0)
      anode = true;
   else if (anodeType.compare("BACK") == 0)
      anode = false;
   else
      return 0;

   if (chType.compare("ENERGY") == 0) {
      // std::cout << "Filling energy with " << moduleNumber << moduleCh << std::endl;
      fEnergyModule[anode][detNumber] = moduleNumber;
      fEnergyChannel[anode][detNumber] = moduleCh;
   }
   if (chType.compare("TIME") == 0) {
      // std::cout << "Filling time with " << moduleNumber << moduleCh << std::endl;
      fTimeModule[anode][detNumber] = moduleNumber;
      fTimeChannel[anode][detNumber] = moduleCh;
   }

   return 1;
}
