#ifndef HTROOTSISTIMESTAMP_H
#define HTROOTSISTIMESTAMP_H

#include "HTRootModule.h"

class HTRootSisTimestamp : public HTRootModule {

private:
   ULong64_t fData[2];

public:
   HTRootSisTimestamp() : HTRootModule("Undefined") {}
   HTRootSisTimestamp(TString name); //! Constructor
   ~HTRootSisTimestamp();            //! Destructor

   virtual void Clear() override;
   ULong64_t GetData(Int_t ch) const { return (ch < 2) ? fData[ch] : 0; }
   void SetData(Int_t ch, ULong64_t data)
   {
      if (ch < 2)
         fData[ch] = data;
   }
   ClassDefOverride(HTRootSisTimestamp, 1)
};

#endif
