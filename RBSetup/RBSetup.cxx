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
#include <RBRunInfo.h>
#include <RBExperimentInfo.h>
#include <RBDAQStackInfo.h>
#include <RBModuleInfo.h>

//______________________________________________________________________________
RBSetup::RBSetup(){

///////////////////////////////////////////////////////////////////////////////////////////
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
//                                GENERAL SETUP                                          //
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
///////////////////////////////////////////////////////////////////////////////////////////

  // Set the setup name and title.
  SetName (gExperimentInfo->GetExperimentName());
  SetTitle(gExperimentInfo->GetExperimentTitle());

  // Instantiate a new RBExperiment object.
  gExperiment = new RBExperiment(gExperimentInfo->GetExperimentName());
  // Initialize data members.
  gExperiment->SetMergedData      (gExperimentInfo->IsDataMerged());  // EVT files have been merged.
  gExperiment->SetEventFilePath   (gRun->GetEvtFilePath());
  gExperiment->SetRootFilePath    (gExperimentInfo->GetRootFilePath());
  gExperiment->SetExperimentNumber(gExperimentInfo->GetExperimentName());
  
  // Definition of electronic modules and stacks
  for(int NumStack=0; NumStack<gRun->GetNStacks(); NumStack++)
  {
    RBUSBStack * newStack = new RBUSBStack();
    newStack->AddStack();
    RBDAQStackInfo * newStackInfo = gRun->GetStackInfo(NumStack);
    for(int NumModule=0; NumModule<newStackInfo->GetNModules(); NumModule++)
    {
      // Register electronics which should/can be unpacked as raw channels.
      // If adding electronics to a USBStack, the order matters unless directly specified
      // as an optional argument when calling AddToStack().
      RBModuleInfo * newModuleInfo = newStackInfo->GetModuleInfo(NumModule);
      newStack->AddToStack(0,newModuleInfo->GetVSN(),newModuleInfo->GetModule());
      newModuleInfo->GetModule()->SetFillData(kTRUE);
    }
    newStack->SetMergedID(newStackInfo->GetStackID());
    newStack->SetBranchName(newStackInfo->GetStackName());
    //The VMUSB stack is the only thing in the electronics list. All of the modules are part
    //of the stack and are unpacked in RBUSBStack::Unpack
    gExperiment->RegisterElectronics(newStack);
  }

  //______________________________________________________________________________
  // Now initialize the classes.
  gExperiment->InitClass();
  printf("Experiment classes correctly initialized\n");
}

RBSetup::~RBSetup(){
  delete gExperiment;
}
