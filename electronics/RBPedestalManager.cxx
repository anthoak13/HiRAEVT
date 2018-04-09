#include "RBPedestalManager.h"

#include <fstream>
#include <string>
#include <sstream>

//______________________________________________________________________________
RBPedestalManager::RBPedestalManager(Int_t ch_num) : 
fPedSet(kFALSE)
{
  fPedestals = (Int_t *)new Int_t[ch_num]();
}

//______________________________________________________________________________
RBPedestalManager::RBPedestalManager(const char * file_name, Int_t ch_num)
{
  fPedestals = (Int_t *)new Int_t[ch_num]();
  if(LoadPedestals(file_name)<0){
    fPedSet=kFALSE;
  }
}

//______________________________________________________________________________
RBPedestalManager::~RBPedestalManager()
{
  delete [] fPedestals; 
}

//______________________________________________________________________________
Int_t RBPedestalManager::LoadPedestals(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn)
  {
    return -1; 
  }
  
  std::string line;  
  while(!FileIn.eof())
  {
    Int_t Ch;
    Int_t Ped;
    
    std::getline(FileIn, line);

    if (line.find('*')==0) continue;
    if (line.empty()) continue;
    
    std::istringstream lineStream(line);
    lineStream>>Ch>>Ped;
    
    fPedestals[Ch]=Ped;
  }
  
  fPedSet=kTRUE;
  return 0;
}

//______________________________________________________________________________
Int_t RBPedestalManager::GetPedestalValue(Int_t ch_num) const
{
  return fPedestals[ch_num];
}

//______________________________________________________________________________
Bool_t RBPedestalManager::IsSet() const
{
  return fPedSet;
}