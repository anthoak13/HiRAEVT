#ifndef HTROOTTIMESTAMP_H
#define HTROOTTIMESTAMP_H

#include <HTRootElectronics.h>
#include <TROOT.h>
#include <TTreeReaderValue.h>

class HTRootTimestamp : public HTRootElectronics {
public:
   HTRootTimestamp(const char *);
   ~HTRootTimestamp();

   void InitTreeInputBranch(TTreeReader &) override;
   Long64_t GetData() const;

private:
   TTreeReaderValue<Long64_t> *fTimestamp;
};

#endif
