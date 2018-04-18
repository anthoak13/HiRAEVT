//
//  RBCAEN1x90Unpacker.h
//

#ifndef __RBCAEN1x90UNPACKER_H
#define __RBCAEN1x90UNPACKER_H

#ifndef __RBMODULEUNPACKER_H
#include "RBModuleUnpacker.h"
#endif

#include "RBElectronics.h"

#include <iostream>
#include <TTree.h>
#include <TRandom3.h>
#include <TNamed.h>
#include <TList.h>


class RBCAEN1x90Unpacker : public RBModuleUnpacker, public RBElectronics
{
private:
  Int_t         fDepth;                             //!
  Int_t         fRefChannel;                        //!
  Int_t         fnChannels;                         //!
  Int_t         fChanmask;                          //!
  Int_t         fChanshift;                         //!
  Int_t         fDatamask;                          //!
  Double_t      fChsToNs;                           //!
  TString       fChName;                            //!
  Int_t         fnCh;                               //!
  Double_t      fTimes[128];                        //!
  TRandom3      *fRandomGen;                        //!
  ULong64_t     fTotalUnpackedData;                 //!
  ULong64_t     fErrorCount;                        //!
  ULong64_t     fNoReferenceCount;                  //!
  ULong64_t     fVSNMismatchCount;                  //!

  TTree               *fChain;                      //! Pointer to current TTree or TChain
  Int_t                fCurrent;                    //! Current Tree number in a TChain

public:
  RBCAEN1x90Unpacker():fDepth(1),fRefChannel(0),fnCh(128){fChName = "Ch";}
  RBCAEN1x90Unpacker(const char* chName, Int_t depth, Int_t refCh, Int_t nChannels, Double_t chsToNs=1);
  ~RBCAEN1x90Unpacker();

  Int_t    DecodeVSN(Int_t header);
  void     reportError(UInt_t errorWord, int slot);

  void     Clear(Option_t *option="");
  void     InitClass();
  void     InitBranch(TTree* tree);
  void     InitTree(TTree* tree);
  Int_t    Unpack(std::vector<UShort_t>& event, UInt_t offset);

  Short_t  GetData(Int_t ch){return (Short_t)Short_t(fTimes[ch]);}
  Double_t GetDataf(Int_t ch){return fTimes[ch];}

  void PrintSummary();
  void  AddTTreeUserInfo(TTree *);

  ClassDef(RBCAEN1x90Unpacker,1);
};

#endif
