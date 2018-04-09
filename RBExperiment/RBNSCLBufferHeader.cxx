
#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TEventList.h>

#ifndef __PACKETID_H
#define __PACKETID_H
#include "packetID.h"
#endif
// #ifndef __RBNSCLBUFFERHEADER_H
// #define __RBNSCLBUFFERHEADER_H
#include "RBNSCLBufferHeader.h"
  //#endif


ClassImp(RBNSCLBufferHeader);

////////////////////////////////////////////////////////////////////////////////
/* BEGIN_HTML
<p> The RBNSCLBufferHeader class provides the structure for holding a typical           
 event buffer header at the NSCL.
</p>
                                                          

<h3><a name="unpack">I. Unpacking</a></h3>

<h3><a name="vars">II. Important Data Members</a></h3>

<h3><a name="examples">III. Examples</a></h3>


END_HTML */
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void RBNSCLBufferHeader::Clear(Option_t *)
{
  // -- Clear the data members
  //

  nwds      = 0;
  type      = 0;
  sequence  = 0;
  nEntities = 0;
}


//______________________________________________________________________________
void RBNSCLBufferHeader::InitClass()
{
  // -- Initialize the class to its default settings.
  //
  
  Clear();
}


//______________________________________________________________________________
void RBNSCLBufferHeader::InitTree(TTree *itree)
{
  // -- Set the branch pointers.
  //

  fChain = itree;
  fCurrent = -1;

  b_nwds      = fChain->GetBranch("nwds");
  b_type      = fChain->GetBranch("type");
  b_sequence  = fChain->GetBranch("sequence");
  b_nEntities = fChain->GetBranch("nEntities");

//   fChain->SetBranchAddress("nwds",&nwds,&b_nwds);
//   fChain->SetBranchAddress("type",&type,&b_type);
//   fChain->SetBranchAddress("sequence",&sequence,&b_sequence);
//   fChain->SetBranchAddress("nEntities",&nEntities,&b_nEntities);
}
