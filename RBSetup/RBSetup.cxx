//Preliminary RBSetup file for unpacking merged HiRA and NW file
//Juan Manfredi, Daniele Dell Aquila


#include "RBSetup.h"
#include "RBUSBStack.h"
#include "RBElectronics.h"
#include "RBTimestamp.h"
#include "RBUSBStackMarker.h"
#include "RBHINPUnpacker.h"
#include "RBPh7xxUnpacker.h"
#include "RBCAEN7xxUnpacker.h"
#include "RBCAEN1x90Unpacker.h"
#include "RBSisTimestampUnpacker.h"

//#include "MCPSettings.C"

//______________________________________________________________________________
RBSetup::RBSetup(){

///////////////////////////////////////////////////////////////////////////////////////////
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
//                                GENERAL SETUP                                          //
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
///////////////////////////////////////////////////////////////////////////////////////////

  // Set the setup name and title.
  SetName ("testBeamSetup");
  SetTitle("NSCL experiment 15190");

  // Instantiate a new RBExperiment object.
  fExperiment = new RBExperiment("NE");
  // Initialize data members.
  fExperiment->SetMergedData      (kTRUE);  // EVT files have been merged.
  fExperiment->SetEventFilePath   ("/mnt/misc/daqevents-ro/e15190_2/experiment/");//TEMPORARY
  fExperiment->SetRootFilePath    ("/mnt/analysis/e15190/TEST_rootfilesRIBbit2/");//TEMPORARY
  fExperiment->SetExperimentNumber("15190");

  //HiRA Stack
  RBSisTimestampUnpacker *timestamp1 = new RBSisTimestampUnpacker("timestamp1");
  RBHINPUnpacker *hinp = new RBHINPUnpacker("hinp",2,kFALSE);
  RBCAEN7xxUnpacker  *adc1 = new RBCAEN7xxUnpacker ("adc1");
  RBCAEN7xxUnpacker  *adc2 = new RBCAEN7xxUnpacker ("adc2");
  RBCAEN1x90Unpacker *csiTDC = new RBCAEN1x90Unpacker("csiTDC",1,48,128,0.1);//Slot 11
  RBCAEN7xxUnpacker *ATqdc = new RBCAEN7xxUnpacker ("ATqdc");
  RBCAEN7xxUnpacker *MBqdc1 = new RBCAEN7xxUnpacker ("MBqdc1");
  RBCAEN7xxUnpacker *MBqdc2 = new RBCAEN7xxUnpacker ("MBqdc2");
  RBCAEN7xxUnpacker *MBqdc3 = new RBCAEN7xxUnpacker ("MBqdc3");
  RBCAEN7xxUnpacker *MBqdc4 = new RBCAEN7xxUnpacker ("MBqdc4");
  RBCAEN7xxUnpacker *MBqdc5 = new RBCAEN7xxUnpacker ("MBqdc5");
  RBCAEN7xxUnpacker *MBqdc6 = new RBCAEN7xxUnpacker ("MBqdc6");
  RBCAEN7xxUnpacker *MBtdc1 = new RBCAEN7xxUnpacker ("MBtdc1");
  RBCAEN7xxUnpacker *MBtdc2 = new RBCAEN7xxUnpacker ("MBtdc2");
  RBCAEN7xxUnpacker *MBtdc3 = new RBCAEN7xxUnpacker ("MBtdc3");
  // Register electronics which should/can be unpacked as raw channels.
  // If adding electronics to a USBStack, the order matters unless directly specified
  // as an optional argument when calling AddToStack().

  RBUSBStack *hiraStack = new RBUSBStack();
  hiraStack->AddStack();
  // Usage: AddToStack(<stackNum>, <slot>, <modulePtr>)

  //Adding timestamp to stack:
  //MAKE CAREFUL NOTE WHETHER OR NOT THIS LINE IS COMMENTED OR NOT
  hiraStack->AddToStack(0,-1,timestamp1);
  hiraStack->AddToStack(0,-1,hinp);
  hiraStack->AddToStack(0,-1,adc1);
  hiraStack->AddToStack(0,-1,adc2);
  hiraStack->AddToStack(0,7,csiTDC);
  //  hiraStack->AddToStack(0,-1,ATqdc);
  hiraStack->AddToStack(0,-1,MBqdc1);
  hiraStack->AddToStack(0,-1,MBqdc2);
  hiraStack->AddToStack(0,-1,MBqdc3);
  hiraStack->AddToStack(0,-1,MBqdc4);
  hiraStack->AddToStack(0,-1,MBqdc5);
  hiraStack->AddToStack(0,-1,MBqdc6);
  hiraStack->AddToStack(0,-1,MBtdc1);
  hiraStack->AddToStack(0,-1,MBtdc2);
  hiraStack->AddToStack(0,-1,MBtdc3);
  //hiraStack->AddToStack(0,endMarker);

  hiraStack->SetBranchName("HiRA Stack");

  fExperiment->RegisterElectronics(hiraStack);

  //NWVW Stack
  // Define the modules in the VME crate that are used in the VMUSB stack.
  RBSisTimestampUnpacker *timestamp2 = new RBSisTimestampUnpacker("timestamp2");
  RBCAEN7xxUnpacker  *qdc1 = new RBCAEN7xxUnpacker ("qdc1");    // Slot 4
  RBCAEN7xxUnpacker  *qdc2 = new RBCAEN7xxUnpacker ("qdc2");    // Slot 5
  RBCAEN7xxUnpacker  *qdc3 = new RBCAEN7xxUnpacker ("qdc3");    // Slot 6
  RBCAEN7xxUnpacker  *qdc4 = new RBCAEN7xxUnpacker ("qdc4");    // Slot 8
  RBCAEN7xxUnpacker  *qdc5 = new RBCAEN7xxUnpacker ("qdc5");    // Slot 9
  RBCAEN7xxUnpacker  *qdc6 = new RBCAEN7xxUnpacker ("qdc6");    // Slot 10
  //  RBCAEN1x90Unpacker *NWTDC = new RBCAEN1x90Unpacker("NWTDC",1,96,128,0.1);//Slot 12
  RBCAEN1x90Unpacker *NWTDC = new RBCAEN1x90Unpacker("NWTDC",1,104,128,0.1);//Slot 12
  RBCAEN7xxUnpacker  *qdc7 = new RBCAEN7xxUnpacker ("qdc7");
  RBCAEN7xxUnpacker  *qdc8 = new RBCAEN7xxUnpacker ("qdc8");
  //  RBCAEN1x90Unpacker *VWTDC = new RBCAEN1x90Unpacker("VWTDC",1,1,128,0.1);//Slot 14
  RBCAEN1x90Unpacker *VWTDC = new RBCAEN1x90Unpacker("VWTDC",1,8,128,0.1);//Slot 14
  RBCAEN7xxUnpacker  *qdcfart = new RBCAEN7xxUnpacker ("qdcfart");

  // Register electronics which should/can be unpacked as raw channels.
  // If adding electronics to a USBStack, the order matters unless directly specified
  // as an optional argument when calling AddToStack().
  RBUSBStack *NWStack = new RBUSBStack();
  NWStack->AddStack();
  // Usage: AddToStack(<stackNum>, <slot>, <modulePtr>)

  NWStack->AddToStack(0,-1,timestamp2);
  NWStack->AddToStack(0,-1,qdc1);
  NWStack->AddToStack(0,-1,qdc2);
  NWStack->AddToStack(0,-1,qdc3);
  NWStack->AddToStack(0,-1,qdc4);
  NWStack->AddToStack(0,-1,qdc5);
  NWStack->AddToStack(0,-1,qdc6);
  NWStack->AddToStack(0,12,NWTDC);
  NWStack->AddToStack(0,-1,qdc7);
  NWStack->AddToStack(0,-1,qdc8);
  NWStack->AddToStack(0,14,VWTDC);
  NWStack->AddToStack(0,-1,qdcfart);

  NWStack->SetBranchName("NW Stack");

  fExperiment->RegisterElectronics(NWStack);
  //The VMUSB stack is the only thing in the electronics list. All of the modules are part
  //of the stack and are unpacked in RBUSBStack::Unpack

  //______________________________________________________________________________
  // Set the built data merged IDs.
  hiraStack->SetMergedID(0);
  NWStack->SetMergedID(1);
  //______________________________________________________________________________
  // Define components to be filled.
  timestamp1 ->SetFillData(kTRUE);
  hinp       ->SetFillData(kTRUE);
  adc1       ->SetFillData(kTRUE);
  adc2       ->SetFillData(kTRUE);
  ATqdc      ->SetFillData(kTRUE);
  MBqdc1     ->SetFillData(kTRUE);
  MBqdc2     ->SetFillData(kTRUE);
  MBqdc3     ->SetFillData(kTRUE);
  MBqdc4     ->SetFillData(kTRUE);
  MBqdc5     ->SetFillData(kTRUE);
  MBqdc6     ->SetFillData(kTRUE);
  MBtdc1     ->SetFillData(kTRUE);
  MBtdc2     ->SetFillData(kTRUE);
  MBtdc3     ->SetFillData(kTRUE);
  timestamp2 ->SetFillData(kTRUE);
  qdc1       ->SetFillData(kTRUE);
  qdc2       ->SetFillData(kTRUE);
  qdc3       ->SetFillData(kTRUE);
  qdc4       ->SetFillData(kTRUE);
  qdc5       ->SetFillData(kTRUE);
  qdc6       ->SetFillData(kTRUE);
  qdc7       ->SetFillData(kTRUE);
  qdc8       ->SetFillData(kTRUE);
  NWTDC      ->SetFillData(kTRUE);
  VWTDC      ->SetFillData(kTRUE);

  //______________________________________________________________________________
  // Now initialize the class.
  // NOTE:  We must do this before we initialize the scaler section.
  printf("---------------- Initializing Classes ------------------------------------\n");
  fExperiment->InitClass();
  printf("--------------------------------------------------------------------------\n\n\n");
}

RBSetup::~RBSetup(){
  delete fExperiment;
}
