#ifndef HTROOTSISTIMESTAMP_H
#define HTROOTSISTIMESTAMP_H

#include "HTRootModule.h"

#include <iostream>

class HTRootSisTimestamp : public HTRootModule {

public:
   ULong64_t fData[2];

   HTRootSisTimestamp() : HTRootModule("Undefined") {}
   HTRootSisTimestamp(TString name); //! Constructor
   ~HTRootSisTimestamp();            //! Destructor

   virtual void Clear() override;
   void PrintData() override { std::cout << fData[0] << " " << fData[1] << std::endl; }
   ULong64_t GetData(Int_t ch) const { return (ch < 2) ? fData[ch] : 0; }
   void SetData(Int_t ch, ULong64_t data)
   {
      if (ch < 2)
         fData[ch] = data;
   }
   ClassDefOverride(HTRootSisTimestamp, 1)
};

#endif
