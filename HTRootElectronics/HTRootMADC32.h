#ifndef HTROOTMADC32_H
#define HTROOTMADC32_H

#include <HTRootElectronics.h>
#include <TROOT.h>
#include <sstream>

class HTRootMADC32 : public HTRootElectronics {
public:
   HTRootMADC32(const char *);
   ~HTRootMADC32();

   Short_t GetData(int) const;                       //! Get the data corresponding to a given channel
   void InitTreeInputBranch(TTreeReader &) override; //! Set Input TTreeReader Branch

private:
   int fNumCh;
};

#endif
