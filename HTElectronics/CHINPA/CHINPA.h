/*!
   Unpacker for XLM/HINP ADC version
*/
#ifndef __CHINPA_H
#define __CHINPA_H

#ifndef __CMODULEUNPACKER_H
#include "CModuleUnpacker.h"
#endif

class CTreeParameterArray;

class CHINPA : public CModuleUnpacker {

public:
   // Canonicals:

   CHINPA();
   virtual ~CHINPA();

   // The unpacker entry:

public:
   virtual unsigned int operator()(CEvent &rEvent, std::vector<unsigned short> &event, unsigned int offset,
                                   CParamMapCommand::AdcMapping *pMap);

private:
   int nMBs;
   CTreeParameterArray ****getTree(CParamMapCommand::AdcMapping *pMap, CEvent &rEvent);
};

#endif
