#ifndef HTTDCSPARECHANNEL_H
#define HTTDCSPARECHANNEL_H

#include <TROOT.h>
#include <string>

class HTTDCSpareChannel {
public:
   HTTDCSpareChannel(const char *);
   ~HTTDCSpareChannel();

   Double_t GetValue() const;
   const Double_t *GetValuePointer() const;
   const char *GetName() const;

   void SetValue(Double_t);

private:
   std::string fname;
   Double_t fvalue;
};

#endif
