


#include <CFilter.h>
#include <iostream>
#include <CRingStateChangeItem.h>
#include <CPhysicsEventItem.h>
#include "CUnpackerFilter.h"
#include "Unpacker.h"
#include "FragmentIndex.h"

#include <iostream>
#include <stdio.h>
#include <string.h>


/**! \class CUnpackerFilter
    Here is a sample implementation of a filter to append a reversed copy of the
    data in physics event to its body. This is for illustration purposes.

    See the documentation for the CFilter base class for the virtually declared
    methods available for dealing with non-physics events. The user has access
    to all of the different ring item types. In fact, it is not necessary for
    the user to return the same type of ring item from method as it received.
*/
CUnpackerFilter::CUnpackerFilter()
{

}

void CUnpackerFilter::PassArguments(int argc, char* argv[])
{
  // Find the --source cmd argument and extract the file path.

  std::cout << "**Pass Arguments to UnpackerFilter**" << std::endl;

  char *result = 0;
  char  temp[500];
  for(int i=1; i<argc; i++){
    const char *sourcePrefix = "source=file:/";
    result = strstr(argv[i], sourcePrefix);
    if(result) strcpy(temp, result+14);

//    const char *debugPrefix = "debug=";
//    result = strstr(argv[i], debugPrefix);
//    if(strcmp(result,"true")==0) gUnpacker.SetDebug(true);
  }
  //if(result==0){ std::cerr << "-->CUnpackerFilter::ctor source argument is invalid." << std::endl;}

  strcpy(sourceFileName,temp);
  std::cout << "**Setting source file name to " << sourceFileName << " **" << std::endl;
  gUnpacker.SetSource(sourceFileName);

  gUnpacker.Clear();
}

// handle the state change events
CRingItem* CUnpackerFilter::handleStateChangeItem(CRingStateChangeItem* pItem)
{
//  std::cout << pItem->getEventTimestamp() << std::endl;
//  std::cout << pItem->getSourceId() << std::endl;
//  std::cout << pItem->getBarrierType() << std::endl;
//  std::cout << pItem->typeName()       << std::endl;
//  std::cout << pItem->getRunNumber()   << std::endl;
//  std::cout << pItem->getElapsedTime() << std::endl;
//  std::cout << pItem->getTimestamp()   << std::endl;
//  std::cout << pItem->getTitle()       << std::endl;

//  if(gUnpacker.IsDataMerged()){
//    gUnpacker(pItem->getEventTimestamp(),  pItem->getSourceId(),
//              pItem->getBarrierType(),     pItem->typeName(),
//              pItem->getRunNumber(),       pItem->getElapsedTime(),
//              pItem->getTimestamp(),       pItem->getTitle());
//  }else{
    gUnpacker(0,                      99,
              0,                      pItem->typeName(),
              pItem->getRunNumber(),  pItem->getElapsedTime(),
              pItem->getTimestamp(),  pItem->getTitle());
//  }

  return pItem;
}

// handle the physics events
CRingItem* CUnpackerFilter::handlePhysicsEventItem(CPhysicsEventItem* pItem)
{
  uint16_t* pBody = reinterpret_cast<uint16_t*>(pItem->getBodyPointer());

  if(gUnpacker.IsDataMerged()){
    // Deal with the built data structure
    // if the physics event item is not the output of the
    // event builder, you don't need this.
    FragmentIndex frags(pBody);

    // Call my root analyzer... the name was externed in the header
    gUnpacker(frags, pItem->getBodySize(),pItem->getEventTimestamp());
//  }else if(gUnpacker.GetDataFormatVersion() >= 11.0){
//  }else if(11.1 >= 11.0){
//
//    gUnpacker(pBody, pItem->getBodySize(),pItem->getEventTimestamp());
  }else{
    // Unmerged data.
    gUnpacker(pBody, pItem->getBodySize());
  }

  // return the original item
  return pItem;
}
