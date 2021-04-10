#ifndef HTMODULEINFO_H
#define HTMODULEINFO_H

#include <HTElectronics.h>

class HTModuleInfo {
public:
   HTModuleInfo();
   ~HTModuleInfo();

   HTElectronics *GetModule() const;
   int GetVSN() const;
   int GetNumCh() const;
   const char *GetModuleType() const;
   const char *GetModuleName() const;
   const char *GetModuleChMapping(int) const;
   double GetModuleChPedestal(int) const;

   void SetModule(HTElectronics *);
   void SetNumCh(int);
   void SetVSN(int);
   void SetModuleType(std::string);
   void SetModuleType(const char *);
   void SetModuleName(std::string);
   void SetModuleName(const char *);
   void SetChannelMapping(int, std::string);
   void SetChannelMapping(int, const char *);
   void SetChannelPedestal(int, double);

private:
   int fNumCh;                  //! Number of channels of the module
   int fModuleVSN;              //! module VSN
   HTElectronics *fModule;      //! HTElectronics object (the module)
   std::string fModuleType;     //! Module Type
   std::string fModuleName;     //! Module Name
   std::string *fModuleMapping; //! Electronics Mapping
   double *fModulePedestal;     //! Pedestal values
};

#endif
