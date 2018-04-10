//
//  RBUSBStackUnpacker.cpp
//
//
//  Created by Andrew Rogers on 3/21/15.
//  Modified by Juan Manfredi
//


#include "RBUSBStack.h"

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
RBUSBStack::RBUSBStack() :
fEventCount(0),
fWordsCount(0),
fVsnErrorCount(0),
fBufferMismatchCount(0),
fUSBTimestamp(0)
{
  // --
  //

  SetEnabled(kTRUE);
  SetFillData(kTRUE);

  // Initialize the list of stacks.
  fStacks = new TList();
}


//______________________________________________________________________________
Int_t RBUSBStack::AddStack()
{
  // --
  //

  fStacks->Add(new TList());
  return 1;
}



//______________________________________________________________________________
Int_t RBUSBStack::AddToStack(Int_t stackIdx, RBUSBStackMarker *marker)
{
  // --
  //

  return AddToStack(stackIdx, marker, -1);
}



//______________________________________________________________________________
Int_t RBUSBStack::AddToStack(Int_t stackIdx, RBUSBStackMarker *marker, Int_t idx)
{
  // --
  //

  TList *stack = (TList*)fStacks->At(stackIdx);
  if(idx==-1){
    stack->AddLast(marker);
  }else if(idx > -1){
    stack->AddAt(marker,idx);
  }else{
    cerr << "-->RBUSBStack::AddToStack  Invalid stack index." << endl;
    return 0;
  }

  return 1;
}



//______________________________________________________________________________
Int_t RBUSBStack::AddToStack(Int_t stackIdx, Int_t geo, RBElectronics *module)
{
  // --
  //

  return AddToStack(stackIdx, geo, module, -1);
}


//______________________________________________________________________________
Int_t RBUSBStack::AddToStack(Int_t stackIdx, Int_t geo, RBElectronics *module, Int_t idx)
{
  // --
  //

  //  cout << "Adding to RBUSBStack: " << module->ClassName() << endl;

  if(strcmp(module->ClassName(),"RBTimestamp")==0){
    fUSBTimestamp = (RBTimestamp*)module;
    cout << "RBUSBStack:: Added timestamp to stack." << endl;
    return 2;
  }
  TList *stack = (TList*)fStacks->At(stackIdx);
  if(idx==-1){
    stack->AddLast(module);
  }else if(idx > -1){
    stack->AddAt(module,idx);
  }else{
    cerr << "-->RBUSBStack::AddToStack  Invalid stack index." << endl;
    return 0;
  }
  module->SetGeo(geo);

  return 1;
}


//______________________________________________________________________________
Int_t RBUSBStack::RemoveFromStack()
{
  // --
  //

  return 1;
}


//______________________________________________________________________________
void RBUSBStack::Clear(Option_t *option)
{
  // --
  //

  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    TIter nextModule(stack);
    while(RBElectronics* module = (RBElectronics*)nextModule()){
      module->Clear(option);
    }
  }

  fEventCount       = 0;

}


//______________________________________________________________________________
void RBUSBStack::InitClass()
{
  // -- Initialize any additional components of this class.
  //

  // Initialize the class for each module in each stack.
  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    TIter nextModule(stack);
    while(RBElectronics* module = (RBElectronics*)nextModule()){
      module->InitClass();
    }
  }
  fUnpackErrorCount = 0;
}


//______________________________________________________________________________
void RBUSBStack::InitBranch(TTree* tree)
{
  // -- Initialize the branch pointers of this class.
  //

  // Initialize the branches for each module in each stack.
  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    TIter nextModule(stack);
    while(RBElectronics* module = (RBElectronics*)nextModule()){
      module->InitBranch(tree);
    }
  }
  cout << "-->RBUSBStack:: Initialized branches." << endl;
  cout.flush();
}


//______________________________________________________________________________
void RBUSBStack::InitTree(TTree* tree)
{
  // -- Initialize this class to a TTree.
  //

  fChain = tree;

  // Initialize the class for each module in each stack.
  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    TIter nextModule(stack);
    while(RBElectronics* module = (RBElectronics*)nextModule()){
      module->InitTree(tree);
    }
  }

}


//______________________________________________________________________________
Int_t RBUSBStack::Unpack(UShort_t *pEvent, UInt_t offset)
{
  // -- Unpack a USB fragment and any defined electronics modules.
  //
  // pEvent should point to the USBStack header.

  //  cout << "Unpacking RBUSBStack: " << endl;

  fEventCount++;          // event counter
  vector<UShort_t> event; // A vector of assembeled event data.
  StackInfo        info;  // Object containing the information about the USBStack.

  Int_t sOffset = 0;

  // Assemble the data into a vector of UShort_t's that we can use.
  //  cout << "Address of pEvent before assembling into vector: " << *pEvent << endl;
  info = assembleEvent(pEvent, event);
  //  cout << "Asembled event " << event[0] << endl;
  //  cout << "First value of event: " << event[0] << endl;
  fWordsCount+=info.s_stackSize+14; // Number of words unpacked for the stack

  // Unpack the fragment timestamp
  //  if(fUSBTimestamp) sOffset = fUSBTimestamp->Unpack(pEvent);

  // Loop over all the defined USB stacks.
  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    // Loop over all the defined modules in this stack.
    // Try to find the module in the buffer using it's vsn.
    // If there is no vsn, then try to find it using the order it was
    // defined in the USBStack.
    // If we still cannot locate the module's data in the buffer, then
    // report the error.
    TIter nextModule(stack);


    while(RBElectronics* module = (RBElectronics*)nextModule()){
      //      cout << "Within stack, module is " << module->GetBranchName() << endl;

      //      cout << "Print out some of the buffer" << endl;
      /*
      for (int i=0; i<24; i++){
	cout << hex << event[sOffset+i] << endl;
      }
      */

      // Search the RingItem body for this module's data.
      // Get the 'header' .. ensure that it matches our VSN if module has a VSN.
      unsigned long header;
      int           vsn = -99;
      Int_t         moduleOffset = sOffset;

      //DEBUG
      //      cout << "Module " << module << endl;
      //      cout << " is called " << module->ClassName() << endl;

      // If this is a Marker, just read it.
      if(strcmp(module->ClassName(),"RBUSBStackMarker")==0){
	      cout << "Found marker: " << module->ClassName() << endl;
        RBUSBStackMarker *marker = (RBUSBStackMarker*)module;
        sOffset = marker->Unpack(event,sOffset);
      }else{
        // Try to unpack the module given the order it was defined in the stack.
        // If the VSN does not match, then search for the VSN in rest of the body.
        header  = getLong(event, sOffset);
        vsn     = module->DecodeVSN(header);

	//DEBUG
	//	cout << "VSN: " << vsn << " " << module->GetName() << " " << module->GetVSN() << " " << sOffset << " " << event[sOffset] << endl;
	//If the VSN is 0, then this is definitely a junk event and I
	//want to escape
	if (vsn == 0) {
	  fVsnErrorCount++;
	  return event.size();
	}
        //WARNING: if vsn = 0 the word is clearly corrupted, but no need to skip the whole event
        /*
	while (vsn == 0)
        {
          sOffset+=2;
          header  = getLong(event, sOffset);
          vsn     = module->DecodeVSN(header);
        }
	*/
        // WARNING: possible bug, here sOffset can be 0 and the following condition can have strange behaviours (temporarly changed)!!!
        if(getLong(event,sOffset)==0xffffffff && (getLong(event,sOffset+1)==0xffffffff || (sOffset>0 && getLong(event,sOffset-1)==0xffffffff))){
          // This event was not properly constructed. Possible missing module data. However, it could be that the modules are simply empty.
          // burn up a set of 0xffff's
          sOffset += 2;
          module->SetUnpackError(10); // Error code.
          fUnpackErrorCount++;
	  //	  cout << "Unpack "Error" Count up to " << fUnpackErrorCount << endl;
  }else if(vsn == module->GetVSN() || module->GetVSN() == -1){sOffset = module->Unpack(event, sOffset);}
        else{
	  //	  cout << "Scanning ringitem body for VSN " << endl;
          // Scan the RingItem body for the VSN of this module.
          while(sOffset<event.size() && vsn != module->GetVSN()){
            header  = getLong(event, sOffset);
            vsn     = module->DecodeVSN(header);
            sOffset += 2;
          }
        }
      }

      //If the offset is nonsense, get out
      if (sOffset == -1) {break;}
//      // If we did not find a VSN, then the module may not have written a VSN.
//      // Try to unpack the module given the order it was defined in the stack.
//      if(sOffset >= event.size()) {
//        cerr << "Did not find our data for VSN " << module->GetVSN() << " " << vsn << ". . ." << endl;
//        sOffset = offset;		// If immed BERR skip the BERR word and give up
//      }
	}
  }

//  offset = event.size();

  // Something went wrong if we didn't burn up the entire event:
  if(sOffset != event.size()) {
    fBufferMismatchCount++;
    cerr << "**WARNING** Event not entirely decoded by unpackers -- READ: "
         << sOffset << " SIZE: " << event.size() << " EVENT: " << fEventCount << endl;
    return event.size();
  }

  return sOffset;
}


//////////////////////////////////////////////////////////////////////////////////
// Utilties

/*
 Assemble an event from the VMUSB event fragments.  While we're at it,
 extract the stack id and return it to the caller.

 */
RBUSBStack::StackInfo
RBUSBStack::assembleEvent(UShort_t *p, vector<UShort_t>& event)
{
  // --
  //

  StackInfo result;
  bool done    = false;
  int  stackId = -1;
  size_t totalSize = 0;
  while(!done) {
    // Decode the header:
    UShort_t header = *p; ++p;
    done            = (header & VMUSB_CONTINUE) == 0;
    int fragmentSize = header & VMUSB_LENGTH;
    totalSize++;		// headers are a word of size...

    // only pull the stackid out of the first header (just in case).
    if (stackId < 0) {
      stackId = (header & VMUSB_STACKID_MASK) >> VMUSB_STACKID_SHIFT;
    }

    // Append the fragment to the event vector
    for (int i=0; i < fragmentSize; i++) {
      UShort_t datum = *p; ++p;
      event.push_back(datum);
    }
    totalSize += fragmentSize;	// Words in the fragment...
  }

  result.s_stackNumber = stackId;
  result.s_stackSize   = totalSize;

  return result;
}

//______________________________________________________________________________
void RBUSBStack::PrintSummary()
{
  printf("**********************************************\n");
  printf("-- %s summary --\n", GetBranchName());
  printf("%llu words read\n", fWordsCount);
  printf("%llu vsn errors\n", fVsnErrorCount);
  printf("%llu events not entirely decoded\n\n",fBufferMismatchCount);
  TIter nextStack(fStacks);
  while(TList* stack = (TList*)nextStack()){
    TIter nextModule(stack);
    while(RBElectronics* module = (RBElectronics*)nextModule()){
      module->PrintSummary();
    }
  }
  printf("**********************************************\n");

  return;
}
