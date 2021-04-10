//
//  HTPh7xxUnpacker.cpp
//
//
//  Created by Andrew Rogers on 3/20/15.
//
//

#include "HTPh7xxUnpacker.h"

#include "HTCCUSBPacket.h"

//#include <stdint.h>
#include <vector>

using namespace std;

ClassImp(HTPh7xxUnpacker)

   void HTPh7xxUnpacker::Clear(Option_t *option)
{
   memset(fData, '\0', fnCh);
}

void HTPh7xxUnpacker::InitClass() {}

void HTPh7xxUnpacker::InitBranch(TTree *tree)
{
   Char_t tmp[500];
   sprintf(tmp, "%s[%i]/s", fChName.Data(), fnCh);
   tree->Branch(fChName, fData, tmp);
}

void HTPh7xxUnpacker::InitTree(TTree *tree)
{
   fChain = tree;
}

/*!
 Unpack data from a Ph7xxx module.  The data packet from this module
 is assumed to be of the form:

 \verbatim
 +----------------------+
 | Packet id            |
 +----------------------+
 | hit pattern          |
 +----------------------+
 |  channel data...     |
 ...                   ...
 +----------------------+

 \endverbatim
 Assumptions:
 - The module is configured to read the hit pattern.
 - The module is read zero suppressed.
 - The caller has verified the id is correct for us.

 @param p           - Byte order translating pointer to the raw event.
 @param pModuleInfo - Pointer to the module info structure.
 this includes the channel->parameter map.
 @param rEvent      - Reference to the unpacked paramter vector.
 @return int
 @retval Number of words of data consumed by this unpacker.
 */
Int_t HTPh7xxUnpacker::Unpack(UShort_t *p)
{
   Clear();

   ++p; // Skip over the id.
   UShort_t hitPattern = *p;
   ++p; // Use the hit pattern to get the data count:
   UShort_t channels = bitsInMask(hitPattern);

   for (Int_t i = 0; i < channels; i++) {
      UShort_t datum = *p;
      ++p;
      Int_t channel = Channel(datum);
      fData[channel] = Value(datum);
   }

   // we consumed the id the bit mask (2) and channels words:

   return 2 + channels;
}
