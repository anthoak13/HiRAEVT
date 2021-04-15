#include <CFilter.h>
#include <CPhysicsEventItem.h>
#include <CRingStateChangeItem.h>
#include <HTFilter.h>
#include <FragmentIndex.h>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>

#include "HTExperimentInfo.h"
#include "HTExperiment.h"



HTFilter::HTFilter(json configJson)
{
   fExperimentInfo = new HTExperimentInfo();
   fExperiment = new HTExperiment();
   CreateUnpackers(configJson["VMEstacks"]);
}

HTFilter::~HTFilter()
{
}

void HTFilter::CreateUnpackers(json moduleList)
{
   for( auto& elem : moduleList)
      std::cout << elem << std::endl;
}

// handle the state change events
CRingItem *HTFilter::handleStateChangeItem(CRingStateChangeItem *pItem)
{
   TDatime time(pItem->getTimestamp());

   switch(pItem->type())
   {
      
      //Its a begin run event, so save the run number, time, and title
   case 1:
      std::cout << "Begin run " << pItem->getRunNumber() << " at "
		<< time.AsString() << std::endl;
      fExperimentInfo->SetStartTime(time);
      fExperimentInfo->SetRunNumber(pItem->getRunNumber());
      fExperimentInfo->SetRunTitle(pItem->getTitle());
      break;
      
      //It's a end run event to save the end time
   case 2:
      std::cout << "End run " << pItem->getRunNumber() << " at "
		<< time.AsString() << std::endl;
      fExperimentInfo->SetEndTime(time);
      break;
   default:
      break;
   }

   return pItem;
}

// handle the physics events
CRingItem *HTFilter::handlePhysicsEventItem(CPhysicsEventItem *pItem)
{
   uint16_t *pBody = reinterpret_cast<uint16_t *>(pItem->getBodyPointer());

   /*
   if (unpacker->IsDataMerged()) {
      // Deal with the built data structure
      // if the physics event item is not the output of the
      // event builder, you don't need this.
      FragmentIndex frags(pBody);

      // Call my root analyzer... the name was externed in the header
      (*unpacker)(frags, pItem->getBodySize(), pItem->getEventTimestamp());
      //  }else if(unpacker->GetDataFormatVersion() >= 11.0){
      //  }else if(11.1 >= 11.0){
      //
      //    unpacker(pBody, pItem->getBodySize(),pItem->getEventTimestamp());
   } else {

      // Unmerged data.
      (*unpacker)(pBody, pItem->getBodySize());
   }
   */
   // return the original item
   return pItem;
}
