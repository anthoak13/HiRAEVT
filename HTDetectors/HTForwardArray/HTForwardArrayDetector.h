#ifndef HTFORWARDARRAYDETECTOR_H
#define HTFORWARDARRAYDETECTOR_H

#include <TROOT.h>

class HTForwardArrayDetector {
private:
   int fnumdet;
   Short_t fE;
   Double_t fTime;

public:
   HTForwardArrayDetector(int);
   ~HTForwardArrayDetector();

   // Setting methods
   void SetE(Short_t);
   void SetTime(Double_t);

   // Getting methods
   Short_t GetE() const;
   Double_t GetTime() const;

   void Clear();
};

#endif
