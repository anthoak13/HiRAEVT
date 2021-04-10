#ifndef HTMICROBALLDETECTOR_H
#define HTMICROBALLDETECTOR_H

#include <TROOT.h>

class HTMicroballDetector {
private:
   Int_t fNumDet;
   Short_t fTail;
   Short_t fFast;
   Short_t fTime;

public:
   HTMicroballDetector(int detector_number);
   ~HTMicroballDetector();

   // Setting methods
   void SetTail(Short_t);
   void SetFast(Short_t);
   void SetTime(Short_t);

   // Getting methods
   Short_t GetTail() const;
   Short_t GetFast() const;
   Short_t GetTime() const;

   void Clear();
};

#endif
