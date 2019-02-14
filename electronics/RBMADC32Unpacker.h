//
//  RBMADC32Unpacker.h
//

#ifndef __RBMADC32UNPACKER_H
#define __RBMADC32UNPACKER_H

#include <RBModuleUnpacker.h>
#include <RBElectronics.h>

#include <TTree.h>
#include <TNamed.h>
#include <TList.h>

/*
 * This unpacker is responsible for unpacking Mesytech 32 channel digitizers.
 * Created by Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 * v1 : 12 February 2019
 */
class RBMADC32Unpacker : public RBModuleUnpacker, public RBElectronics
{
private:
  TString  fChName;                            //!
  Int_t    fnCh;                               //!
  Short_t  fData[32];                          //!
  ULong64_t     fTotalUnpackedCount;           //!
  ULong64_t     fOverflowCount;                //!
  ULong64_t     fVSNMismatchCount;             //!


  TTree               *fChain;                 //! Pointer to current TTree or TChain
  Int_t                fCurrent;               //! Current Tree number in a TChain


public:
  RBMADC32Unpacker():fnCh(32){fChName = "Ch";}
  RBMADC32Unpacker(const char* chName);
  ~RBMADC32Unpacker();

  Int_t   DecodeVSN(Int_t header);

  void    Clear(Option_t *option="");
  void    InitClass();
  void    InitBranch(TTree* tree);
  void    InitTree(TTree* tree);
  Int_t   Unpack(std::vector<UShort_t>& event, UInt_t offset);

  Short_t *GetData(){return fData;}
  Short_t GetData(Int_t ch){return fData[ch];}

  void PrintSummary();
  void AddTTreeUserInfo(TTree *);

  ClassDef(RBMADC32Unpacker,1);
};

#endif
