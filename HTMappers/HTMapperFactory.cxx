// Implementation of HTDetectorMapperFactory

#include "HTMapperFactory.h"

#include "TTree.h"

#include "HTDetectorMapper.h"
#include "HTSimpleDetector.h"
#include "HTSimpleDetectorMapper.h"

#include <string>

#include "nlohmann/json.hpp"

HTMapperFactory *HTMapperFactory::_instance = nullptr;

HTMapperFactory *HTMapperFactory::Instance()
{

   if (_instance == nullptr)
      _instance = new HTMapperFactory();
   return _instance;
}

HTDetectorMapper *HTMapperFactory::CreateDetector(const json &detConfig, TTree *tr)
{
   HTDetectorMapper *mapper = nullptr;
   TString detType = detConfig["detectorType"].get<std::string>();

   if (detType.EqualTo("HTSimpleDetector")) {
      mapper = new HTSimpleDetectorMapper(detConfig);
      if (tr != nullptr)
         tr->Branch(mapper->GetDetector()->GetName(), (HTSimpleDetector *)mapper->GetDetector());
   }

   if (mapper == nullptr)
      throw std::invalid_argument(std::string("Detector type ").append(detType).append(" is not defined!"));

   return mapper;
}
