//
//  HTUSBStackUnpacker.cpp
//
//
//  Created by Andrew Rogers on 3/21/15.
//  Modified by Juan Manfredi
//

#include "HTUSBStack.h"

// Constants

static const UShort_t VMUSB_STACKID_MASK(0xe000);
static const UShort_t VMUSB_STACKID_SHIFT(13);
static const UShort_t VMUSB_CONTINUE(0x1000);
static const UShort_t VMUSB_LENGTH(0x0fff);

// Constants:

// All data words have these bits:

static const UInt_t ALLH_TYPEMASK(0x7000000);
static const UInt_t ALLH_TYPESHIFT(24);
static const UInt_t ALLH_GEOMASK(0xf8000000);
static const UInt_t ALLH_GEOSHIFT(27);

// High part of header.

static const UInt_t HDRH_CRATEMASK(0x00ff0000);
static const UInt_t HDRH_CRATESHIFT(16);

// Low part of header.
static const UInt_t HDRL_COUNTMASK(0X3f00);
static const UInt_t HDRL_COUNTSHIFT(8);

// High part of data:

static const UInt_t DATAH_CHANMASK(0x3f0000);
static const UInt_t DATAH_CHANSHIFT(16);

// Low part of data

static const UInt_t DATAL_UNBIT(0x2000);
static const UInt_t DATAL_OVBIT(0x1000);
static const UInt_t DATAL_VBIT(0x40000);
static const UInt_t DATAL_DATAMASK(0x0fff);

//  High part of trailer:- index in event to the first unprocessed word of the event.

static const UInt_t TRAILH_EVHIMASK(0x00ff0000);

// Word types:

static const UInt_t HEADER(2);
static const UInt_t DATA(0);
static const UInt_t TRAILER(4);
static const UInt_t INVALID(6);

//______________________________________________________________________________
HTUSBStack::HTUSBStack() : fEventCount(0), fWordsCount(0), fVsnErrorCount(0), fBufferMismatchCount(0), fUSBTimestamp(0)
{
   // --
   //

   SetEnabled(kTRUE);
   SetFillData(kTRUE);

   // Initialize the list of stacks.
   fStacks = new TList();
}

//______________________________________________________________________________
Int_t HTUSBStack::AddStack()
{
   // --
   //

   fStacks->Add(new TList());
   return 1;
}

//______________________________________________________________________________
Int_t HTUSBStack::AddToStack(Int_t stackIdx, HTUSBStackMarker *marker)
{
   // --
   //

   return AddToStack(stackIdx, marker, -1);
}

//______________________________________________________________________________
Int_t HTUSBStack::AddToStack(Int_t stackIdx, HTUSBStackMarker *marker, Int_t idx)
{
   // --
   //

   TList *stack = (TList *)fStacks->At(stackIdx);
   if (idx == -1) {
      stack->AddLast(marker);
   } else if (idx > -1) {
      stack->AddAt(marker, idx);
   } else {
      cerr << "-->HTUSBStack::AddToStack  Invalid stack index." << endl;
      return 0;
   }

   return 1;
}

//______________________________________________________________________________
Int_t HTUSBStack::AddToStack(Int_t stackIdx, Int_t geo, HTElectronics *module)
{
   // --
   //

   return AddToStack(stackIdx, geo, module, -1);
}

//______________________________________________________________________________
Int_t HTUSBStack::AddToStack(Int_t stackIdx, Int_t geo, HTElectronics *module, Int_t idx)
{
   // --
   //

   //  cout << "Adding to HTUSBStack: " << module->ClassName() << endl;

   if (strcmp(module->ClassName(), "HTTimestamp") == 0) {
      fUSBTimestamp = (HTTimestamp *)module;
      cout << "HTUSBStack:: Added timestamp to stack." << endl;
      return 2;
   }
   TList *stack = (TList *)fStacks->At(stackIdx);
   if (idx == -1) {
      stack->AddLast(module);
   } else if (idx > -1) {
      stack->AddAt(module, idx);
   } else {
      cerr << "-->HTUSBStack::AddToStack  Invalid stack index." << endl;
      return 0;
   }
   module->SetGeo(geo);

   return 1;
}

//______________________________________________________________________________
Int_t HTUSBStack::RemoveFromStack()
{
   // --
   //

   return 1;
}

//______________________________________________________________________________
void HTUSBStack::Clear(Option_t *option)
{
   // --
   //

   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         module->Clear(option);
      }
   }

   // fEventCount       = 0;
}

//______________________________________________________________________________
void HTUSBStack::InitClass()
{
   // -- Initialize any additional components of this class.
   //

   // Initialize the class for each module in each stack.
   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         module->InitClass();
      }
   }
   fUnpackErrorCount = 0;
}

//______________________________________________________________________________
void HTUSBStack::InitBranch(TTree *tree)
{
   // -- Initialize the branch pointers of this class.
   //

   // Initialize the branches for each module in each stack.
   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         module->InitBranch(tree);
      }
   }
   cout.flush();
}

//______________________________________________________________________________
void HTUSBStack::InitTree(TTree *tree)
{
   // -- Initialize this class to a TTree.
   //

   fChain = tree;

   // Initialize the class for each module in each stack.
   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         module->InitTree(tree);
      }
   }
}

//______________________________________________________________________________
Int_t HTUSBStack::Unpack(UShort_t *pEvent, UInt_t offset)
{
   // -- Unpack a USB fragment and any defined electronics modules.
   //
   // pEvent should point to the USBStack header.
   // Assumes that there could be extra pairs of ffffs
   // and skips over them

   fEventCount++;          // event counter
   vector<UShort_t> event; // A vector of assembeled event data.
   StackInfo info;         // Object containing the information about the USBStack.

   Int_t sOffset = 0;

   // Assemble the data into a vector of UShort_t's that we can use.
   info = assembleEvent(pEvent, event);

   fWordsCount += info.s_stackSize + 14; // Number of words unpacked for the stack

   // Loop over all the defined USB stacks.
   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      // Loop over all the defined modules in this stack.
      // Try to find the module in the buffer using it's vsn.
      // If there is no vsn, then try to find it using the order it was
      // defined in the USBStack.
      // If we still cannot locate the module's data in the buffer, then
      // report the error.
      TIter nextModule(stack);

      while (HTElectronics *module = (HTElectronics *)nextModule()) {

         // Search the RingItem body for this module's data.
         // Get the 'header' .. ensure that it matches our VSN if module has a VSN.
         unsigned long header;
         int vsn = -99;

         // If this is a Marker, just read it.
         if (strcmp(module->ClassName(), "HTUSBStackMarker") == 0) {

            cout << "Found marker: " << module->ClassName() << endl;
            HTUSBStackMarker *marker = (HTUSBStackMarker *)module;

            sOffset = marker->Unpack(event, sOffset);
            if (sOffset == -1) {
               break;
            }
         }

         // Try to unpack the module given the order it was defined in the stack.
         // If the VSN does not match, then search for the VSN in rest of the body.
         while (event[sOffset] == 0xffff)
            sOffset++;

         // Make sure wer're in a good region
         if (sOffset > event.size() - 2)
            break;

         header = getLong(event, sOffset);
         // Get the VSN
         vsn = module->DecodeVSN(header);

         // cout << "VSN: " << vsn << " " << module->GetName() << " " << module->GetVSN() << " " << sOffset << " " <<
         // hex << event[sOffset] << endl;

         if (vsn == module->GetVSN() || module->GetVSN() == -1) {
            // cout << "Unpacking: " << dec << vsn << " " << module->GetName() << endl;
            sOffset = module->Unpack(event, sOffset);
         }
         // else
         // cout << "Skipping unpacking of " << dec << vsn << " " << module->GetName() << endl;

         // If the offset is nonsense, get out
         if (sOffset == -1) {
            break;
         }

      } // end while loop over modules

   } // end loop over stacks

   // Clear out any remaining ffffs
   while (event[sOffset] == 0xffff)
      sOffset++;

   // Something went wrong if we didn't burn up the entire event:
   if (sOffset < event.size()) {
      fBufferMismatchCount++;

#ifdef DEBUG
      cerr << "**WARNING** Event not entirely decoded by unpackers -- READ: " << sOffset << " SIZE: " << event.size()
           << " EVENT: " << fEventCount << endl;

      for (int i = 0; i < event.size(); i++) {
         if (i % 4 == 0)
            cout << endl;
         cout << " " << hex << event[i];
      }
      cout << std::endl;
#endif // End if debug

      return event.size();
   }

   // cout << "Finished with event" << endl << endl;
   return sOffset;
}

//////////////////////////////////////////////////////////////////////////////////
// Utilties

/*
 Assemble an event from the VMUSB event fragments.  While we're at it,
 extract the stack id and return it to the caller.

 */
HTUSBStack::StackInfo HTUSBStack::assembleEvent(UShort_t *p, vector<UShort_t> &event)
{
   // --
   //

   StackInfo result;
   bool done = false;
   int stackId = -1;
   size_t totalSize = 0;
   while (!done) {

      // Decode the header:
      UShort_t header = *p++;
      done = (header & VMUSB_CONTINUE) == 0;
      int fragmentSize = header & VMUSB_LENGTH;
      totalSize++; // headers are a word of size...

      // only pull the stackid out of the first header (just in case).
      if (stackId < 0) {
         stackId = (header & VMUSB_STACKID_MASK) >> VMUSB_STACKID_SHIFT;
      }

      // Append the fragment to the event vector
      for (int i = 0; i < fragmentSize; i++) {
         UShort_t datum = *p++;
         event.push_back(datum);
      }
      totalSize += fragmentSize; // Words in the fragment...
   }

   result.s_stackNumber = stackId;
   result.s_stackSize = totalSize;

   return result;
}

//______________________________________________________________________________
void HTUSBStack::PrintSummary()
{
   printf("**********************************************\n");
   printf("-- %s summary --\n", GetBranchName());
   printf("%llu words read\n", fWordsCount);
   printf("%llu vsn errors\n", fVsnErrorCount);
   printf("%llu events not entirely decoded\n\n", fBufferMismatchCount);
   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         module->PrintSummary();
      }
   }
   printf("**********************************************\n");

   return;
}

//______________________________________________________________________________
void HTUSBStack::AddTTreeUserInfo(TTree *tree)
{
   TNamed *wordsRead = new TNamed(Form("%s : Words Read", GetBranchName()), Form("%llu", fWordsCount));
   TNamed *VSNErrors = new TNamed(Form("%s : VSN Errors", GetBranchName()), Form("%llu", fVsnErrorCount));
   TNamed *bufferMismatches =
      new TNamed(Form("%s : Events Not Entirely Decoded", GetBranchName()), Form("%llu", fBufferMismatchCount));

   tree->GetUserInfo()->Add(wordsRead); // Number of words read in the stack
   tree->GetUserInfo()->Add(VSNErrors); // Number of VSN errors found in the stack
   tree->GetUserInfo()->Add(
      bufferMismatches); // Number of events not entirely decoded by the unpacker for the current stack

   TIter nextStack(fStacks);
   while (TList *stack = (TList *)nextStack()) {
      TIter nextModule(stack);
      while (HTElectronics *module = (HTElectronics *)nextModule()) {
         if (module->GetFillData()) {
            module->AddTTreeUserInfo(tree);
         }
      }
   }

   return;
}
