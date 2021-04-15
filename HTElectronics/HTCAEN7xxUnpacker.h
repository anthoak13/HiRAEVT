//
//  HTCAEN7xxUnpacker.h
//

#ifndef __HTCAEN7xxUNPACKER_H
#define __HTCAEN7xxUNPACKER_H

#include "HTElectronics.h"

#include <TList.h>
#include <TNamed.h>
#include <TTree.h>

/*!
 This unpacker is responsible for unpacking CAEN 32 channel digitizers.  These modules
 include the CAEN V775, 785, 792, and 862 modules.  These modules have a
 virtual slot number.  Furthermore it is possible that the readout of a specific
 module may be completely supressed.  Fortunately the header of a module is
 quite unambiguous and this unpacker can deal with that case just fine.
 */
class HTCAEN7xxUnpacker :  public HTElectronics {
private:
   TString fChName;               //!
   Int_t fnCh;                    //!
   Short_t fData[32];             //!
   ULong64_t fTotalUnpackedCount; //!
   ULong64_t fOverflowCount;      //!
   ULong64_t fVSNMismatchCount;   //!

   TTree *fChain;  //! Pointer to current TTree or TChain
   Int_t fCurrent; //! Current Tree number in a TChain

public:
   HTCAEN7xxUnpacker() : fnCh(32) { fChName = "Ch"; }
   HTCAEN7xxUnpacker(const char *chName);
   ~HTCAEN7xxUnpacker();

   Int_t DecodeVSN(Int_t header) override;

   void Clear(Option_t *option = "") override;
   void InitBranch(TTree *tree) override;
   void InitTree(TTree *tree) override;
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   Short_t *GetData() { return fData; }
   Short_t GetData(Int_t ch) override{ return fData[ch]; }
   Double_t GetDataf(Int_t ch) override{ return fData[ch]; }

   void PrintSummary() override;
   void Print() override { std::cout << fChName << std::endl; }
   void AddTTreeUserInfo(TTree *) override;

   ClassDefOverride(HTCAEN7xxUnpacker, 1);
};

#endif
