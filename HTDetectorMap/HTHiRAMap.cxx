#include <HTHiRAMap.h>

//________________________________________________
HTHiRAMap::HTHiRAMap(const std::string& name, int num_telescopes) :
  HTDetectorMap(name),
  fNumTelescopes(num_telescopes),
  fNumStripsperTelescope(N_STRIPS_PER_TELESCOPE),
  fNumCsIperTelescope(N_CSIS_PER_TELESCOPE),
  fCsIEnergyModule(0),
  fCsIEnergyChannel(0),
  fCsITimeModule(0),
  fCsITimeChannel(0),
  fModuleEF(0),
  fModuleEB(0),
  fStripEF(0),
  fStripEB(0)
{
  fCsIEnergyModule = new int *[fNumTelescopes];
  fCsIEnergyChannel = new int *[fNumTelescopes];
  fCsITimeModule = new int *[fNumTelescopes];
  fCsITimeChannel = new int *[fNumTelescopes];
  fModuleEF = new int [fNumTelescopes];
  fModuleEB = new int [fNumTelescopes];
  fStripEF = new int ***[fNumTelescopes];
  fStripEB = new int ***[fNumTelescopes];

  for(int i=0; i<fNumTelescopes; i++) {
    fCsIEnergyModule[i] = new int [fNumCsIperTelescope];
    fCsIEnergyChannel[i] = new int [fNumCsIperTelescope];
    fCsITimeModule[i] = new int [fNumCsIperTelescope];
    fCsITimeChannel[i] = new int [fNumCsIperTelescope];
  }

  for(int Ntel=0; Ntel<fNumTelescopes; Ntel++) {
    fStripEF[Ntel]= new int **[N_HINP_BANKS];
    fStripEB[Ntel]= new int **[N_HINP_BANKS];
    for(int NBank=0; NBank<N_HINP_BANKS; NBank++) {
      fStripEF[Ntel][NBank]=new int *[N_HINP_CHIPS_PER_BANK];
      fStripEB[Ntel][NBank]=new int *[N_HINP_CHIPS_PER_BANK];
      for(int NChip=0; NChip<N_HINP_CHIPS_PER_BANK; NChip++) {
        fStripEF[Ntel][NBank][NChip]=new int [N_HINP_CHANNELS_PER_CHIP];
        fStripEB[Ntel][NBank][NChip]=new int [N_HINP_CHANNELS_PER_CHIP];
      }
    }
  }

  Clear();
}

//________________________________________________
HTHiRAMap::~HTHiRAMap()
{
  if(fCsIEnergyModule) {
    for(int i=0; i<fNumTelescopes; i++) {
      if(fCsIEnergyModule[i]) delete [] fCsIEnergyModule[i];
    }
    delete fCsIEnergyModule;
  }
  if(fCsIEnergyChannel) {
    for(int i=0; i<fNumTelescopes; i++) {
      if(fCsIEnergyChannel[i]) delete [] fCsIEnergyChannel[i];
    }
    delete fCsIEnergyChannel;
  }
  if(fCsITimeModule) {
    for(int i=0; i<fNumTelescopes; i++) {
      if(fCsITimeModule[i]) delete [] fCsITimeModule[i];
    }
    delete fCsITimeModule;
  }
  if(fCsITimeChannel) {
    for(int i=0; i<fNumTelescopes; i++) {
      if(fCsITimeChannel[i]) delete [] fCsITimeChannel[i];
    }
    delete fCsITimeChannel;
  }
  if(fModuleEF) delete [] fModuleEF;
  if(fModuleEB) delete [] fModuleEB;
  for(int Ntel=0; Ntel<fNumTelescopes; Ntel++) {
    for(int NBank=0; NBank<N_HINP_BANKS; NBank++) {
      for(int NChip=0; NChip<N_HINP_CHIPS_PER_BANK; NChip++) {
        if(fStripEF) {
          delete [] fStripEF[Ntel][NBank][NChip];
        }
        if(fStripEB) {
          delete [] fStripEB[Ntel][NBank][NChip];
        }
      }
      if(fStripEF[Ntel][NBank]) {
        delete [] fStripEF[Ntel][NBank];
      }
      if(fStripEB[Ntel][NBank]) {
        delete [] fStripEB[Ntel][NBank];
      }
    }
    if(fStripEF[Ntel]) {
      delete [] fStripEF[Ntel];
    }
    if(fStripEB[Ntel]) {
      delete [] fStripEB[Ntel];
    }
  }
  if(fStripEF) {
    delete [] fStripEF;
  }
  if(fStripEB) {
    delete [] fStripEB;
  }
}

//________________________________________________
void HTHiRAMap::Clear()
{
  fModuleAssignmentOrder->clear();
  for(int i=0; i<fNumTelescopes; i++) {
    for(int j=0; j<fNumCsIperTelescope; j++) {
      fCsIEnergyModule[i][j]=-1;
      fCsIEnergyChannel[i][j]=-1;
      fCsITimeModule[i][j]=-1;
      fCsITimeChannel[i][j]=-1;
    }
  }
  for(int Ntel=0; Ntel<fNumTelescopes; Ntel++) {
    for(int NBank=0; NBank<N_HINP_BANKS; NBank++) {
      for(int NChip=0; NChip<N_HINP_CHIPS_PER_BANK; NChip++) {
        for(int NChannel=0; NChannel<N_HINP_CHANNELS_PER_CHIP; NChannel++) {
          fStripEF[Ntel][NBank][NChip][NChannel]=-1;
          fStripEB[Ntel][NBank][NChip][NChannel]=-1;
        }
      }
    }
  }
  for(int i=0; i<fNumTelescopes; i++) {
    fModuleEF[i]=-1;
    fModuleEB[i]=-1;
  }
}

//________________________________________________
int HTHiRAMap::ParseMapLine(const char * line_to_parse)
{
  std::string LineReadCommentLess(line_to_parse);
  std::istringstream LineStream(LineReadCommentLess.substr(LineReadCommentLess.find("map ")+4));
  std::string DetectorName;
  std::string ChName;
  std::string DetectorToSet;
  std::string ModuleName;
  LineStream>>DetectorName>>ChName>>DetectorToSet>>ModuleName;
  if(DetectorName.compare(fName)!=0) return 0;

  DetectorToSet.assign(DetectorToSet.substr(DetectorToSet.find("detector=\"")+10,DetectorToSet.find_last_of("\"")-(DetectorToSet.find("detector=\"")+10)));
  ModuleName.assign(ModuleName.substr(ModuleName.find("module=\"")+8,ModuleName.find_last_of("\"")-(ModuleName.find("module=\"")+8)));

  int ModuleNumber=(*fModuleAssignmentOrder)[ModuleName];

  if(ChName.compare("EF")==0 || ChName.compare("EB")==0) {
    int TelNumber=std::stoi(DetectorToSet);
    if(ChName.compare("EF")==0) fModuleEF[TelNumber]=ModuleNumber;
    if(ChName.compare("EF")==0) fModuleEB[TelNumber]=ModuleNumber;
    //assignment of EF/EB bank, chip, ch -> strip mapping
    std::string MotherBoardName;
    std::string ChipBoardName;
    LineStream>>MotherBoardName>>ChipBoardName;
    MotherBoardName.assign(MotherBoardName.substr(MotherBoardName.find("motherboard=\"")+13,MotherBoardName.find_last_of("\"")-(MotherBoardName.find("motherboard=\"")+13)));
    ChipBoardName.assign(ChipBoardName.substr(ChipBoardName.find("chipboard=\"")+11,ChipBoardName.find_last_of("\"")-(ChipBoardName.find("chipboard=\"")+11)));
    int MotherBoardNumber=std::stoi(MotherBoardName);
    int ChipBoardNumber=std::stoi(ChipBoardName);
    for(int NChip=0; NChip<N_HINP_CHIP_PER_CHIPBOARD; NChip++) {
      for(int NChannel=0; NChannel<N_HINP_CHANNELS_PER_CHIP; NChannel++) {
        //WARNING: chipboard and chip numbers start from 1
        // In such a way we will have chipboards from 1 to 14 and chips from 1 to 28 for each bank
        int AbsoluteNChip=(ChipBoardNumber-1)*N_HINP_CHIP_PER_CHIPBOARD+NChip+1;
        //WARNING: the assignment algorithm of strip E order within a chip is fixed, modify here to change it
        // motherboard(bank)
        //  |- chipboard 1
        //  |  - chip 1
        //  |      - ch 0 -> strip 0
        //  |      - ch 1 -> strip 2
        //  |      - ch 2 -> strip 4
        //  |      - (...)
        //  |  - chip 2
        //  |      - ch 0 -> strip 1
        //  |      - ch 1 -> strip 3
        //  |      - ch 2 -> strip 5
        //  |      - (...)
        //  (...)
        if(ChName.compare("EF")==0) fStripEF[TelNumber][MotherBoardNumber][AbsoluteNChip-1][NChannel]=NChannel*2*(1-NChip%2)+(NChip%2)*(2*NChannel+1);
        if(ChName.compare("EB")==0) fStripEB[TelNumber][MotherBoardNumber][AbsoluteNChip-1][NChannel]=NChannel*2*(1-NChip%2)+(NChip%2)*(2*NChannel+1);
      }
    }

  } else if (ChName.compare("DE")==0) {
  } else if (ChName.compare("CSIENE")==0) {
    int TelNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("TEL")+3, DetectorToSet.find("_")-(DetectorToSet.find("TEL")+3)));
    int CsINumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("CsI")+3));
    std::string ModuleChannelString;
    LineStream>>ModuleChannelString;
    ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));
    int ModuleChannel=std::stoi(ModuleChannelString);
    fCsIEnergyModule[TelNumber][CsINumber]=ModuleNumber;
    fCsIEnergyChannel[TelNumber][CsINumber]=ModuleChannel;
  } else if (ChName.compare("CSITIME")==0) {
    int TelNumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("TEL")+3, DetectorToSet.find("_")-(DetectorToSet.find("TEL")+3)));
    int CsINumber=std::stoi(DetectorToSet.substr(DetectorToSet.find("CsI")+3));
    std::string ModuleChannelString;
    LineStream>>ModuleChannelString;
    ModuleChannelString.assign(ModuleChannelString.substr(ModuleChannelString.find("channel=\"")+9,ModuleChannelString.find_last_of("\"")-(ModuleChannelString.find("channel=\"")+9)));
    int ModuleChannel=std::stoi(ModuleChannelString);
    fCsITimeModule[TelNumber][CsINumber]=ModuleNumber;
    fCsITimeChannel[TelNumber][CsINumber]=ModuleChannel;
  }

  return 1;
}
