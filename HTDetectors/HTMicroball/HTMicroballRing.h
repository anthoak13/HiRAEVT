#ifndef HTMICROBALLRING_H
#define HTMICROBALLRING_H

#include <HTMicroballDetector.h>
#include <TROOT.h>

class HTMicroballRing {
private:
   Int_t fNumRing;                           //! ring number starting from 1
   Int_t fNumDetectors;                      //! number of detectors in the ring
   HTMicroballDetector **fMicroballDetector; //! array of Microball signle detectors

public:
   HTMicroballRing(int ring_number, int number_of_detectors); //!
   ~HTMicroballRing();                                        //!

   int GetRingNumber() const;                   //!
   int GetNumberDetectors() const;              //!
   HTMicroballDetector *GetDetector(int) const; //!

   void Clear();
};

#endif
