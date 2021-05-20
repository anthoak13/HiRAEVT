// Implementation of HTDetectorMapperFactory

#include "HTMapperFactory.h"

#include "TTree.h"

#include "HTDetectorMapper.h"
#include "HTMcp.h"
#include "HTMcpMapper.h"
#include "HTMusicIC.h"
#include "HTMusicICMapper.h"
#include "HTSimpleDetector.h"
#include "HTSimpleDetectorMapper.h"
#include "HTTimestamp.h"
#include "HTTimestampMapper.h"

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
      return mapper;
   }
   if (detType.EqualTo("HTMcp")) {
      mapper = new HTMcpMapper(detConfig);
      if (tr != nullptr)
         tr->Branch(mapper->GetDetector()->GetName(), (HTMcp *)mapper->GetDetector());
      return mapper;
   }
   if (detType.EqualTo("HTMusicIC")) {
      mapper = new HTMusicICMapper(detConfig);
      if (tr != nullptr)
         tr->Branch(mapper->GetDetector()->GetName(), (HTMusicIC *)mapper->GetDetector());
      return mapper;
   }
   if (detType.EqualTo("HTTimestamp")) {
      mapper = new HTTimestampMapper(detConfig);
      if (tr != nullptr)
         tr->Branch(mapper->GetDetector()->GetName(), (HTTimestamp *)mapper->GetDetector());
      return mapper;
   }

   throw std::invalid_argument(std::string("Detector type ").append(detType).append(" is not defined!"));
}
