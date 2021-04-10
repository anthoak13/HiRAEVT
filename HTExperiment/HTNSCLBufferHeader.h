
#ifndef __HTNSCLBUFFERHEADER_H
#define __HTNSCLBUFFERHEADER_H

#include <TBranch.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// HTNSCLBufferHeader                                                          //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

class HTNSCLBufferHeader : public TObject {

private:
public:
   UShort_t nwds;      // Number of used words in the buffer.
   UShort_t type;      // Type of data in the buffer.
   Long64_t sequence;  // Buffer sequence number.
   UShort_t nEntities; // Number of entities in the buffer.

   TBranch *b_nwds;      //! nwds branch.
   TBranch *b_type;      //! type branch.
   TBranch *b_sequence;  //! sequence branch.
   TBranch *b_nEntities; //! nEntities branch.

   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

public:
   HTNSCLBufferHeader() {}
   ~HTNSCLBufferHeader() {}

   void Clear(Option_t *option = "");
   void InitClass(); // Calls all InitClass methods.
   void InitTree(TTree *itree);

   ClassDef(HTNSCLBufferHeader, 1)
};

#endif
