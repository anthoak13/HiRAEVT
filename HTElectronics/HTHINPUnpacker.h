#ifndef __HTHINPUnpakcer_H
#define __HTHINPUnpakcer_H

#ifndef __HTMODULEUNPACKER_H
#include "HTModuleUnpacker.h"
#endif

#include "TTree.h"

#include "HTElectronics.h"
#include "HTHINPHit.h"

class HTHINPUnpacker : public HTModuleUnpacker, public HTElectronics {
private:
   Int_t fnMBs;                //! Number of total MBs for all XLMs to be read.
   Bool_t fUsingSISFADC;       //! Using SIS FADC for digitization?
   Bool_t fFoundBeginMarker;   //! Found "begin" marker flag.
   Int_t fReportNExtraMarkers; //!
   ULong64_t fNUnpackedEvents; //!

   ULong64_t fTotalUnpackedData; //!
   ULong64_t fFaultyCount;       //!
   ULong64_t fErrorCount;        //!

   TString fChName;     //! Channel label
   Int_t fnCh;          //!
   UShort_t fGroupMask; //
   HTHINPHit fHits;     //  Collection of triggered HINP channels.

   TTree *fChain;  //! Pointer to current TTree or TChain
   Int_t fCurrent; //! Current Tree number in a TChain

public:
   TBranch *b_fTimestamp; //!
   TBranch *b_fGroupMask; //!
   TBranch *b_fHits;      //!

public:
   HTHINPUnpacker(const char *name, Int_t nMBs, Bool_t usingFADC);
   ~HTHINPUnpacker();

   // The unpacker entry:

public:
   void AddHit(Int_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch, UShort_t chip, UShort_t Hi, UShort_t Lo,
               UShort_t time); // Add a hit to the HTHINPHit object fHits

   Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset);

   void Clear(Option_t *option = "");
   void InitClass() {}
   void InitBranch(TTree *);
   void InitTree(TTree *);

   void PrintSummary();
   void AddTTreeUserInfo(TTree *);

   ClassDef(HTHINPUnpacker, 1);
};

#endif
