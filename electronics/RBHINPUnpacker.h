#ifndef __RBHINPUnpakcer_H
#define __RBHINPUnpakcer_H

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBElectronics.h"

#include "TClonesArray.h"
#include "TTree.h"

static const UShort_t fgMaxXLMs = 4;

class RBHINPHit : public TObject
{
private:
  UShort_t fXLMIndex;   // XLM index
  UShort_t fBank;       // XLM BANK (A=0, B=1)
  UShort_t fGlobalBank; // XLM global BANK ID
  Bool_t   fChMismatch; // XLM/FADC ch mismatch
  UShort_t fChannel;    // chip channel
  UShort_t fChip;       // chip number
  UShort_t fEnergyHi;     // raw energy
  UShort_t fEnergyLo;     // raw energy
  UShort_t fTime;       // raw time
  
public:
  RBHINPHit(){Clear();}
  virtual ~RBHINPHit() {Clear();}
  
  void Clear(){ fXLMIndex = 99;
    fBank       = 99;
    fGlobalBank = 99;
    fChMismatch = kFALSE;
    fChannel    = 99;
    fChip       = 99;
    fEnergyHi     = 0;
    fEnergyLo     = 0;
    fTime       = 0;}
  
  //  void Set(UShort_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch, UShort_t chip, UShort_t energy, UShort_t time){
  void Set(UShort_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch, UShort_t chip, UShort_t Hi, UShort_t Lo, UShort_t time){
    fXLMIndex = xlm; fBank = bank; fGlobalBank = 2*fXLMIndex+fBank;
    fChannel  = ch;  fChip = chip; fEnergyHi     = Hi; fEnergyLo   = Lo;  fTime = time;
  };
  
  UShort_t GetXLM()       {return fXLMIndex;}
  UShort_t GetBank()      {return fBank;   }
  UShort_t GetGlobalBank(){return fGlobalBank;}
  Bool_t   GetChMismatch(){return fChMismatch;}
  UShort_t GetChannel()   {return fChannel;}
  UShort_t GetChip()      {return fChip;   }
  UShort_t GetEnergyLo()    {return fEnergyLo; }
  UShort_t GetEnergyHi()    {return fEnergyHi; }
  UShort_t GetTime()      {return fTime;   }
  
  ClassDef(RBHINPHit,2);
  
};


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
  
  UShort_t  fBankMB[fgMaxXLMs][2];              //! MB # to XLM BANK
  
  TString   fChName;                            //! Channel label
  Int_t     fnCh;                               //!
  ULong64_t fTimestamp[2];                      //
  UShort_t  fGroupMask;                         //
  UShort_t  fData[fgMaxXLMs][32];               //! XLM data
  Int_t     fNHits;                             //
  TClonesArray        *fHits;                   //  Collection of triggered HINP channels.
  static TClonesArray *fgHits;                  //  Collection of triggered HINP channels.
  
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
  RBHINPHit *AddHit(Int_t xlm, UShort_t bank, Bool_t mismatch, UShort_t ch, UShort_t chip,
                    UShort_t Hi, UShort_t Lo, UShort_t time); // Add a hit to the clones array.
  
  Int_t      Unpack(std::vector<UShort_t>& event, UInt_t offset);
  
  void Clear(Option_t *option="");
  void InitClass(){}
  void InitBranch(TTree*);
  void InitTree(TTree*);
  
  UShort_t         GetBankMB(Int_t xlm, char  bank);        // Get the BANK MB Id.
  UShort_t         GetBankMBByIndex(Int_t xlm, Int_t bank); // Get the BANK MB Id.
  TClonesArray *GetHits(){return fHits;}      // Get the "hits" array.
  
  void  SetBankMB(Int_t xlm, char bank, Int_t mb);   // Set the BANK MB Id.
  
  void PrintSummary();  

  ClassDef(RBHINPUnpacker,2);
};



#endif
