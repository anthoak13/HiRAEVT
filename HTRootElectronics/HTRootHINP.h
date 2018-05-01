#ifndef HTROOTHINP_H
#define HTROOTHINP_H

#include <TROOT.h>
#include <HTRootElectronics.h>
#include <RBHINPHit.h>

class HTRootHINP : public HTRootElectronics
{
public :
  HTRootHINP(const char *);
  ~HTRootHINP();

  TTreeReaderValue<RBHINPHit> * GetDataPointer() const;    //!Get a pointer to the TTreeReader value 
  void InitTreeInputBranch(TTreeReader&) override;         //!Set Input TTreeReader Branch

private :
  TTreeReaderValue<RBHINPHit> * fData;

};

#endif
