//
//  HTCAEN1x90Unpacker.h
//

#ifndef HTCAEN1x90UNPACKER_H
#define HTCAEN1x90UNPACKER_H

#include "HTModuleUnpacker.h"

#include <TList.h>
#include <TNamed.h>
#include <TRandom3.h>
#include <TTree.h>
#include <iostream>

class HTCAEN1x90Unpacker : public HTModuleUnpacker {
private:
   static const int MAX_CHANNELS = 128;

   Int_t fDepth;                              //!
   Int_t fRefChannel;                         //!
   Int_t fnChannels;                          //!
   Int_t fChanmask;                           //!
   Int_t fChanshift;                          //!
   Int_t fDatamask;                           //!
   Double_t fChsToNs;                         //!
   TString fChName;                           //!
   Int_t fnCh;                                //!
   TRandom3 *fRandomGen;                      //!
   ULong64_t fTotalUnpackedData;              //!
   ULong64_t fErrorCount;                     //!
   ULong64_t fNoReferenceCount;               //!
   ULong64_t fVSNMismatchCount;               //!

public:
   HTCAEN1x90Unpacker(TString name, Int_t refCh, Int_t nChannels, Double_t chsToNs);
   ~HTCAEN1x90Unpacker();

   void reportError(UInt_t errorWord, int slot);

   Int_t DecodeVSN(Int_t header) override;
   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) override;

   void PrintSummary() override;
   void Print() override { std::cout << fChName << std::endl; }

   ClassDefOverride(HTCAEN1x90Unpacker, 1);
};

#endif
