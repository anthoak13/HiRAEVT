#ifndef HTROOTSISTIMESTAMP_H
#define HTROOTSISTIMESTAMP_H

#include "HTRootModule.h"

class HTRootSisTimestamp : public HTRootModule {

private:
   ULong64_t fData[2];


public:
   HTRootSisTimestamp(TString name); //! Constructor
   ~HTRootSisTimestamp();            //! Destructor

   ULong64_t GetData(int ch) const { if(ch < 2) return fData[ch]; return 0; }

   ClassDef(HTRootSisTimestamp, 1)
   
};

#endif
