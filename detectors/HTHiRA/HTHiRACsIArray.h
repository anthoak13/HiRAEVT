#ifndef HTHIRACSIARRAY_H
#define HTHIRACSIARRAY_H

#include <HTHiRACsI.h>

class HTHiRACsIArray
{
public :
  HTHiRACsIArray();                    //!Constructor
  ~HTHiRACsIArray();                   //!Destructor

  void Clear();                        //!Clear

  int GetNumCsI() const;               //!Get Number of CsIs in the array
  HTHiRACsI * GetCsI(int) const;       //!Get HTHiRACsI object for a certain CsI

private :
  int fNumCsI;                         //!Number of CsI in the array
  HTHiRACsI **fHiRACsI;                //!Array of HiRACsI objects

};

#endif
