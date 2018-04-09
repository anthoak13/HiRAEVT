//
//  RBCAEN7xxUnpacker.h
//

#ifndef __RBCAEN7xxUNPACKER_H
#define __RBCAEN7xxUNPACKER_H

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBElectronics.h"
#include "RBPedestalManager.h"

#include "TTree.h"

/*!
 This unpacker is responsible for unpacking CAEN 32 channel digitizers.  These modules
 include the CAEN V775, 785, 792, and 862 modules.  These modules have a
 virtual slot number.  Furthermore it is possible that the readout of a specific
 module may be completely supressed.  Fortunately the header of a module is
 quite unambiguous and this unpacker can deal with that case just fine.
 */
class RBCAEN7xxUnpacker : public RBModuleUnpacker, public RBElectronics
{
private:
  TString  fChName;                            //!
  Int_t    fnCh;                               //!
  Bool_t   fPedestalSuppression;               //!  
  Short_t  fData[32];                          //!
  ULong64_t     fTotalUnpackedCount;           //!  
  ULong64_t     fOverflowCount;                //! 
  ULong64_t     fVSNMismatchCount;             //!
  
  
  TTree               *fChain;                 //! Pointer to current TTree or TChain
  Int_t                fCurrent;               //! Current Tree number in a TChain
  
  RBPedestalManager   *fPedManager;            //! Pedestal values
  
public:
  RBCAEN7xxUnpacker():fnCh(32),fPedestalSuppression(0){fChName = "Ch";}
  RBCAEN7xxUnpacker(const char* chName);
  ~RBCAEN7xxUnpacker();
  
  Int_t   DecodeVSN(Int_t header);
  
  void    Clear(Option_t *option="");
  void    InitClass();
  void    InitBranch(TTree* tree);
  void    InitTree(TTree* tree);
  Int_t   Unpack(std::vector<UShort_t>& event, UInt_t offset);
  
  void    SetPedestalSuppression(Bool_t PedSuppr){fPedestalSuppression = PedSuppr;}  
  Int_t   SetPedestals(const char *);
  
  Bool_t  GetPedestalSuppression(){return fPedestalSuppression;}
  void    SuppressPedestals();
  Short_t *GetData(){return fData;}
  Short_t GetData(Int_t ch){return fData[ch];}
  
  void PrintSummary();
  
  ClassDef(RBCAEN7xxUnpacker,1);
};

#endif
