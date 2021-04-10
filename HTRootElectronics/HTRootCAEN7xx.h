#ifndef HTROOTCAEN7XX_H
#define HTROOTCAEN7XX_H

#include <HTRootElectronics.h>
#include <TROOT.h>
#include <sstream>

class HTRootCAEN7xx : public HTRootElectronics {
public:
   HTRootCAEN7xx(const char *);
   ~HTRootCAEN7xx();

   TTreeReaderArray<Short_t> *GetDataPointer() const; //! Get the pointer to TTreeReaderArray
   Short_t GetData(int) const;                        //! Get the data corresponding to a given channel
   void InitTreeInputBranch(TTreeReader &) override;  //! Set Input TTreeReader Branch
   int LoadPedestals(const char *);                   //! Load Module Pedestals

private:
   int fNumCh;
   TTreeReaderArray<Short_t> *fData;
   double *fPedestals;
   bool fPedestalsLoaded;
   Short_t fOverflow;
};

#endif
