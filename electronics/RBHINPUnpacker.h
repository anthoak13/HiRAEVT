#ifndef __RBHINPUnpakcer_H
#define __RBHINPUnpakcer_H

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBElectronics.h"

#include "TTree.h"

#include "RBHINPHit.h"

class RBHINPUnpacker :  public RBModuleUnpacker, public RBElectronics
{
private:
  Int_t     fnMBs;                              //! Number of total MBs for all XLMs to be read.
  Bool_t    fUsingSISFADC;                      //! Using SIS FADC for digitization?
  Bool_t    fFoundBeginMarker;                  //! Found "begin" marker flag.
  Int_t     fReportNExtraMarkers;               //!
  ULong64_t fNUnpackedEvents;                   //!

  ULong64_t fTotalUnpackedData;                 //!
  ULong64_t fFaultyCount;                       //!
  ULong64_t fErrorCount;                        //!

  TString   fChName;                            //! Channel label
  Int_t     fnCh;                               //!
  UShort_t  fGroupMask;                         //
  RBHINPHit fHits;                              //  Collection of triggered HINP channels.

  TTree    *fChain;                             //! Pointer to current TTree or TChain
  Int_t     fCurrent;                           //! Current Tree number in a TChain

public:
  TBranch  *b_fTimestamp;                        //!
  TBranch  *b_fGroupMask;                        //!
  TBranch  *b_fHits;                             //!

public:
  RBHINPUnpacker(const char* name, Int_t nMBs, Bool_t usingFADC);
  ~RBHINPUnpacker();

  // The unpacker entry:

public:
  void AddHit(Int_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch, UShort_t chip,
                    UShort_t Hi, UShort_t Lo, UShort_t time); // Add a hit to the RBHINPHit object fHits

  Int_t Unpack(std::vector<UShort_t>& event, UInt_t offset);

  void Clear(Option_t *option="");
  void InitClass(){}
  void InitBranch(TTree*);
  void InitTree(TTree*);

  void PrintSummary();
  void AddTTreeUserInfo(TTree *);

  ClassDef(RBHINPUnpacker,1);
};



#endif
