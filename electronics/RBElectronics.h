//
//  RBElectronics.h
//
//
//  Created by Andrew Rogers on 3/20/15.
//  Modified by Juan Manfredi
//

#ifndef ____RBElectronics__
#define ____RBElectronics__

#include <stdio.h>

#include <TObject.h>
#include <TTree.h>

class RBElectronics : public TObject
{
private:
  TString         fBranchName;             //!
  Int_t           fGeo;                    //! Module slot number or geographical address.
  Int_t           kMergedID;               //! The merged data ID.
  Bool_t          fFill;                   //! Fill data when unpacking.
  Bool_t          fEnabled;                //! Is the module in the data stream?

  UShort_t        fUnpackError;            // Unpacking error code.

public:
  Int_t           fUnpackErrorCount;

public:
  virtual ~RBElectronics(){};

  virtual void  InitClass()              = 0;
  virtual void  InitBranch(TTree* tree)  = 0;
  virtual void  InitTree(TTree* tree)    = 0;
  virtual Int_t Unpack(UShort_t *pEvent)               { return 0;};
  virtual Int_t Unpack(UShort_t *pEvent, UInt_t offset){ return 0;};
  virtual Int_t Unpack(std::vector<UShort_t>& event,
                       UInt_t offset)                  { return 0;};

  virtual Int_t   DecodeVSN(Int_t header){return -1;}

  const char *GetBranchName(){return fBranchName;}
  Bool_t      GetEnabled()   {return fEnabled;}
  Bool_t      GetFillData()  {return fFill;}
  Int_t       GetMergedID()  {return kMergedID;}
  Int_t       GetVSN()       {return fGeo;}
  UShort_t    GetUnpackError(){return fUnpackError;}
  Int_t       GetUnpackErrorCount(){return fUnpackErrorCount;}

  void  SetBranchName(const char *bname){fBranchName = bname;}
  void  SetEnabled( Bool_t enabled)  {fEnabled     = enabled;}
  void  SetFillData(Bool_t fill)     {fFill        = fill;}
  void  SetGeo(Int_t geo)            {fGeo         = geo;}
  void  SetMergedID(Int_t ID)        {kMergedID    = ID;}
  void  SetUnpackError(UShort_t code){fUnpackError = code;}//

  virtual Short_t  GetData(Int_t ch){return -1;}
  virtual Double_t GetDataf(Int_t ch){return -1;}

  virtual void PrintSummary() {return;}
  virtual void AddTTreeUserInfo(TTree *) {return;}

  ClassDef(RBElectronics,1);
};
#endif /* defined(____RBElectronics__) */
