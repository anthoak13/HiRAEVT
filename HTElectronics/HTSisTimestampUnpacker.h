//
//  HTSisTimestampUnpacker.h
//
// WARNING: This class has been introduced during experiment 15190 to handle
// 2 different timestamps, one for the conventional electronics and another one
// for the Korean electronics (that was under test during e15190)
// For a future experiment this should be taken into account.
//

#ifndef __HTSisTimestampUNPACKER_H
#define __HTSisTimestampUNPACKER_H


#include "TTree.h"

#include "HTElectronics.h"

//#include <stdint.h>

// Based on SpecTcl code written by Kyle Brown, adapted for RIBbit by Juan Manfredi
// Made more general by Adam Anthony Feb 2020
// Jan 2018

class HTSisTimestampUnpacker :  public HTElectronics {
private:
   ULong64_t fTimestamp[2];

   TTree *fChain;  //! Pointer to current TTree or TChain
   Int_t fCurrent; //! Current Tree number in a TChain

public:
   HTSisTimestampUnpacker(const char *chName);
   ~HTSisTimestampUnpacker();

   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   //  Int_t   *GetData()        {return fTimes;}

   virtual void InitBranch(TTree *tree) override;
   virtual void Clear();

   virtual void InitClass() override {}
   //  virtual void InitBranch(TTree* tree);
   //  virtual void InitBranch(TTree* tree){}

   virtual void InitTree(TTree *tree) override { fChain = tree; }
   void Print() override { std::cout << "SisTimestamp" << std::endl; }
   void PrintSummary() override { std::cout << "SisTimestamp" << std::endl; }
   virtual Short_t GetData(Int_t ch) override {return -1;}
   virtual Double_t GetDataf(Int_t ch) override {return -1;}
   virtual void AddTTreeUserInfo(TTree *) override {}


   ULong64_t GetTimestamp(unsigned int ch) { return (ch < 2 ? fTimestamp[ch] : 0); }

   ClassDefOverride(HTSisTimestampUnpacker, 1);
};

#endif
