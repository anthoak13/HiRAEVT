#ifndef HTROOTHINP_H
#define HTROOTHINP_H

#include <HTHINPHit.h>
#include <HTRootElectronics.h>
#include <TROOT.h>

class HTRootHINP : public HTRootElectronics {
public:
   HTRootHINP(const char *);
   ~HTRootHINP();

   TTreeReaderValue<HTHINPHit> *GetDataPointer() const; //! Get a pointer to the TTreeReader value
   void InitTreeInputBranch(TTreeReader &) override;    //! Set Input TTreeReader Branch

private:
   TTreeReaderValue<HTHINPHit> *fData;
};

#endif
