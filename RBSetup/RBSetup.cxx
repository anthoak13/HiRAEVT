//Preliminary RBSetup file for unpacking merged HiRA and NW file
//Juan Manfredi, Daniele Dell Aquila

#include <RBSetup.h>

//______________________________________________________________________________
RBSetup::RBSetup(){

///////////////////////////////////////////////////////////////////////////////////////////
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
//                                GENERAL SETUP                                          //
// ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo00000ooooo //
///////////////////////////////////////////////////////////////////////////////////////////

  // Set the setup name and title.
  SetName (gExperimentInfo->GetName());
  SetTitle(gExperimentInfo->GetTitle());

  // Instantiate a new RBExperiment object.
  gExperiment = new RBExperiment(gExperimentInfo->GetName());
  // Initialize data members.
  gExperiment->SetMergedData      (gExperimentInfo->IsDataMerged());  // EVT files have been merged.
  gExperiment->SetEventFilePath   (gRun->GetEvtFilePath());
  gExperiment->SetRootFilePath    (gExperimentInfo->GetRootFilePath());
  gExperiment->SetExperimentNumber(gExperimentInfo->GetName());

  // Definition of electronic modules and stacks
  for(int NumStack=0; NumStack<gRun->GetNStacks(); NumStack++)
  {
    RBUSBStack * newStack = new RBUSBStack();
    newStack->AddStack();
    HTDAQStackInfo * newStackInfo = gRun->GetStackInfo(NumStack);

    printf("RBSetup> Defined new DAQ Stack \"%s\"\n", newStackInfo->GetStackName());

    for(int NumModule=0; NumModule<newStackInfo->GetNModules(); NumModule++)
    {
      // Register electronics which should/can be unpacked as raw channels.
      // If adding electronics to a USBStack, the order matters unless directly specified
      // as an optional argument when calling AddToStack().
      // WARNING: RBHINPUnpacker, RBSisTimestampUnpacker and RBTimestamp have negative VSN. In such a case we give to RBUSBStack::AddToStack() vsn=-1
      HTModuleInfo * newModuleInfo = newStackInfo->GetModuleInfo(NumModule);
      newStack->AddToStack(0,newModuleInfo->GetVSN(),newModuleInfo->GetModule());
      newModuleInfo->GetModule()->SetFillData(kTRUE);

      printf("RBSetup> Added module \"%s\" of type %s to the stack \"%s\"\n", newModuleInfo->GetModuleName(), newModuleInfo->GetModuleType(), newStackInfo->GetStackName());
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

RBSetup::~RBSetup()
{}
