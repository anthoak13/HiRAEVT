#ifndef HTTSTAMPROOTEVENT_H
#define HTTSTAMPROOTEVENT_H

#include <TROOT.h>
#include <stdexcept>

class HTSisTimestampData {
private:
   const static int MAXNUMDET = 10;

public:
   Int_t fMulti;

   ULong64_t *fTimestamp; //[fMulti]

   HTSisTimestampData(int numDet = MAXNUMDET);

   virtual ~HTSisTimestampData();

   ClassDef(HTSisTimestampData, 1);
};

class HTSisTimestampRootEvent {

public:
   HTSisTimestampData fSisTimestamp;

   HTSisTimestampRootEvent(int);
   virtual ~HTSisTimestampRootEvent();

   ClassDef(HTSisTimestampRootEvent, 1);
};

#endif
