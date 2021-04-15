#ifndef HTROOTELECTRONICS_H
#define HTROOTELECTRONICS_H

#include "TObject.h"
#include "TString.h"

// Virtual base clase for ROOT versions of modules

class HTRootModule : public TObject {

protected:
   TString fName;

public:
   HTRootModule(TString name); //! Constructor
   virtual ~HTRootModule();    //! Destructor

   virtual void Clear() = 0;

   virtual const char *GetName() const override { return fName.Data(); }
   TString GetName() { return fName; }

   ClassDefOverride(HTRootModule, 1)
};

#endif
