#include <HTRootCAEN7xx.h>

//________________________________________________
HTRootCAEN7xx::HTRootCAEN7xx(const char * name) : HTRootElectronics(name),
fNumCh(32),
fData(0),
fPedestals(0),
fPedestalsLoaded(false),
fOverflow(4096)
{
  fPedestals = new double[fNumCh];
  for(int i=0; i<fNumCh; i++) {
    fPedestals[i]=0;
  }
}

//________________________________________________
HTRootCAEN7xx::~HTRootCAEN7xx()
{
  if(fData) delete [] fData;
  if(fPedestals) delete [] fPedestals;
}

//________________________________________________
Short_t HTRootCAEN7xx::GetData(int ch) const
{
  double datum=(*fData)[ch];
  if(datum!=fOverflow) {
    datum-=fPedestals[ch];
  }
  return datum>=0 ? datum : -9999;
}

//________________________________________________
TTreeReaderArray<Short_t> * HTRootCAEN7xx::GetDataPointer() const
{
  return fData;
}

void HTRootCAEN7xx::InitTreeInputBranch(TTreeReader& theReader)
{
  fData = new TTreeReaderArray<Short_t>(theReader, GetName());
}

int HTRootCAEN7xx::LoadPedestals(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      if(LineReadCommentLess.find("pedestal ")!=std::string::npos) {
        LineReadCommentLess.assign(LineReadCommentLess.substr(LineReadCommentLess.find("pedestal ")+9));
        std::istringstream LineStream(LineReadCommentLess);
        std::string ModuleToSet;
        int chToSet;
        double ValueToSet;
        LineStream>>ModuleToSet>>chToSet>>ValueToSet;

        if(fName.compare(ModuleToSet)==0) {
          fPedestals[chToSet]=ValueToSet;
          NRead++;
        }
      }
    }
  }
  FileIn.close();

  fPedestalsLoaded=true;
  return NRead;
}
