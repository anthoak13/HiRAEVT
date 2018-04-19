//
//  RBPh7xxUnpacker.h
//
//
//  Created by Andrew Rogers on 3/20/15.
//
//

#ifndef ____RBPh7xxUnpacker__
#define ____RBPh7xxUnpacker__

#include <stdio.h>

#ifndef ____RBCCUSBPacket__
#include "RBCCUSBPacket.h"
#endif

#include "RBElectronics.h"

#include "TTree.h"


/*!
 This class is intended to unpack data from the
 Phillips 7xxx series of digitizers.

 */
class RBPh7xxUnpacker : public RBCCUSBPacket, public RBElectronics
{
private:
  TString  fChName;                            //!
  Int_t    fnCh;                               //!
  UShort_t fData[16];                          //!

  TTree               *fChain;                 //! Pointer to current TTree or TChain
  Int_t                fCurrent;               //! Current Tree number in a TChain

public:
  RBPh7xxUnpacker():fnCh(16){fChName = "Ch";};
  RBPh7xxUnpacker(const char* chName):fChName(chName),fnCh(16){};
  ~RBPh7xxUnpacker(){};

  void    Clear(Option_t *option="");
  void    InitClass();
  void    InitBranch(TTree* tree);
  void    InitTree(TTree* tree);
  Int_t   Unpack(UShort_t *pEvent);

  ClassDef(RBPh7xxUnpacker,1);
};

// Simple utility functions (macros)

// Channel field of the data:

static inline Int_t Channel(UShort_t datum)
{
  return (datum >> 12) & 0xf;
}

// Conversion field of the data:

static inline Int_t Value(UShort_t datum)
{
  return (datum & 0xfff);
}

#endif /* defined(____RBPh7xxUnpacker__) */
