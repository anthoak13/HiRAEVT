/* Implementation for Singeleton factory for detector creation
 *
 * Adam Anthony 7/25/2019
 *
 */
#include "HTDetectorFactory.h"

#include <iostream>


HTDetectorFactory *HTDetectorFactory::_instance = nullptr;

HTDetectorFactory::HTDetectorFactory() {}

HTDetectorFactory::~HTDetectorFactory() {}

HTDetectorFactory *HTDetectorFactory::Instance()
{
   if (_instance == nullptr) {
      _instance = new HTDetectorFactory();
   }

   return _instance;
}

HTDetector *HTDetectorFactory::CreateDetector(const std::string &detType, const std::string &detName, const int numDets)
{
   HTDetector *newDet = nullptr;

   if (newDet == nullptr)
      std::cerr << "The detector type " << detType << " was not recognized." << std::endl;


   return newDet;
}
