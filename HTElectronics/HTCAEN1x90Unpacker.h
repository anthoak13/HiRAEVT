//
//  HTCAEN1x90Unpacker.h
//

#ifndef HTCAEN1x90UNPACKER_H
#define HTCAEN1x90UNPACKER_H

#include "HTElectronics.h"

#include <TList.h>
#include <TNamed.h>
#include <TRandom3.h>
#include <TTree.h>
#include <iostream>

class HTCAEN1x90Unpacker : public HTElectronics {
private:
   static const int MAX_CHANNELS = 128;
   static const int MAX_DEPTH = 16;

   Int_t fDepth;                              //!
   Int_t fRefChannel;                         //!
   Int_t fnChannels;                          //!
   Int_t fChanmask;                           //!
   Int_t fChanshift;                          //!
   Int_t fDatamask;                           //!
   Double_t fChsToNs;                         //!
   TString fChName;                           //!
   Int_t fnCh;                                //!
   Double_t fTimes[MAX_CHANNELS * MAX_DEPTH]; //!
   TRandom3 *fRandomGen;                      //!
   ULong64_t fTotalUnpackedData;              //!
   ULong64_t fErrorCount;                     //!
   ULong64_t fNoReferenceCount;               //!
   ULong64_t fVSNMismatchCount;               //!

   TTree *fChain;  //! Pointer to current TTree or TChain
   Int_t fCurrent; //! Current Tree number in a TChain

public:
   HTCAEN1x90Unpacker() : fDepth(1), fRefChannel(0), fnCh(128) { fChName = "Ch"; }
   HTCAEN1x90Unpacker(const char *chName, Int_t depth, Int_t refCh, Int_t nChannels, Double_t chsToNs = 1);
   ~HTCAEN1x90Unpacker();

   Int_t DecodeVSN(Int_t header) override;
   void reportError(UInt_t errorWord, int slot);

   void Clear(Option_t *option = "") override;
   void InitClass() override;
   void InitBranch(TTree *tree) override;
   void InitTree(TTree *tree) override;
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   Short_t GetData(Int_t ch) override { return (Short_t)Short_t(fTimes[ch]); }
   Double_t GetDataf(Int_t ch) override { return fTimes[ch]; }

   void PrintSummary() override;
   void Print() override { std::cout << fChName << std::endl; }
   void AddTTreeUserInfo(TTree *) override;

   ClassDefOverride(HTCAEN1x90Unpacker, 1);
};

#endif
