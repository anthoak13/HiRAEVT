#ifndef __HTMODULEUNPACKER_H
#define __HTMODULEUNPACKER_H

//
//#ifndef __CPARAMMAPCOMMAND_H
//#include "CParamMapCommand.h"
//#endif

#ifndef __STL_VECTOR
#include <vector>
#ifndef __STL_VECTOR
#define __STL_VECTOR
#endif
#endif

// Forward definitions:
// class CEvent;

/*!
 This is the abstract base class for module unpackers used by the CStackUnpacker
 class.  A concrete class must be created for each actual module type.
 The key method each class must implement is, of course the operator() method.
 This method must unpack the next chunk of the event into the parameters defined
 by its parameter map.  The operator must return a pointer to the next
 unconsumed part of the event.
 */
class HTModuleUnpacker {
private:
   unsigned long fTotalUnpackedWords; //!

   // Canonicals:
public:
   virtual ~HTModuleUnpacker(); // To support destructor chaining in a complex class hierarchy.

   void SetTotalUnpackedWords(unsigned long nWords) { fTotalUnpackedWords = nWords; }

   // pure virtual functions:

protected:
   static unsigned long getLong(std::vector<unsigned short> &event, unsigned int offset);
   virtual unsigned long GetTotalUnpackedWords() { return fTotalUnpackedWords; }
};

#endif