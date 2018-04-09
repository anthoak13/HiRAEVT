{
  cout<<"\nHello"<<endl;
  cout<<"Welcome to RIBbit"<<endl;
  
  printf("   (o)--(o)\n");
  printf("  /.______.\\ \n");
  printf("  \\________/\n");
  printf(" ./        \\.\n");
  printf("( .        , )\n");
  printf(" \\ \\_\\\\//_/ /\n");
  printf("  ~~  ~~  ~~\n");



  // Load required libraries
  gROOT->ProcessLine(".L $RIBbitLIB/libRBNucleus.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBParticleGate.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBHistoUtils.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBEnergyLoss.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBAme.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBElectronics.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBExperiment.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBSetup.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBHiRA.so");
  gROOT->ProcessLine(".L $RIBbitLIB/libRBMcpTrack.so");
  


  gROOT->ProcessLine(".include $RIBbitSRC/detectors/RBDetector");
  gROOT->ProcessLine(".include $RIBbitSRC/utilities/RBAme");
  gROOT->ProcessLine(".include $RIBbitSRC/utilities/RBNucleus");
  gROOT->ProcessLine(".include $RIBbitSRC/utilities/RBEnergyLoss");
  gROOT->ProcessLine(".include $RIBbitSRC/utilities/RBParticleGate");
  gROOT->ProcessLine(".include $RIBbitSRC/utilities/RBHistoUtils");
  gROOT->ProcessLine(".include $RIBbitSRC/detectors/RBHiRA");
  gROOT->ProcessLine(".include $RIBbitSRC/electronics");


  //NPTool stuff
  //TString NPLPath = gSystem->Getenv("NPTOOL");
  //gROOT->ProcessLine(Form(".x %s/NPLib/scripts/NPToolLogon.C+", NPLPath.Data() ) );


  // Adjust the style
  TStyle *style = new TStyle("RIBbitStyle","The default RIBbit style");
  style->SetOptDate(21);
  style->SetOptStat(0);
  style->SetCanvasColor(kGray);
  style->SetPadColor(kWhite);
  style->SetNumberContours(200);
  style->SetFrameLineWidth(3);
  style->SetTitleYOffset(1.2);
  style->SetLabelSize(0.025,"X");
  style->SetLabelSize(0.025,"Y");
  
 
  gROOT->SetStyle("RIBbitStyle");
  gROOT->ForceStyle();
  //gStyle->SetPalette(53);//dark to light radiator
  gStyle->SetPalette(54);//blue to yellow, kBird
  //gStyle->SetPalette(56);//light to dark radiator
  //gStyle->SetPalette(55);//the dreaded rainbow
  gStyle->SetOptStat("mMen");
  gStyle->UseCurrentStyle();

  
  // Create the experimental setup.
  RBSetup      *NESetup = new RBSetup();
  RBExperiment *NE      = NESetup->GetInitializedExp();

  //Initialize HiRA
  RBHiRA *theHiRA;
  theHiRA = (RBHiRA)NE->GetDetectorList()->At(0);



}

