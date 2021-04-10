#include <HTHiRACsIArray.h>

/* WARNING: HiRA number of CsIs per telescope is fixed */
const int N_CSI = 4;
/******************************************************************/

//________________________________________________
HTHiRACsIArray::HTHiRACsIArray() : fNumCsI(N_CSI), fHiRACsI(0)
{
   fHiRACsI = new HTHiRACsI *[fNumCsI];
   for (int NumCsI = 0; NumCsI < fNumCsI; NumCsI++) {
      fHiRACsI[NumCsI] = new HTHiRACsI();
   }
}

//________________________________________________
HTHiRACsIArray::~HTHiRACsIArray()
{
   if (!fHiRACsI)
      return;
   for (int NumCsI = 0; NumCsI < fNumCsI; NumCsI++) {
      if (fHiRACsI[NumCsI])
         delete fHiRACsI[NumCsI];
   }
   if (fHiRACsI)
      delete[] fHiRACsI;
}

//________________________________________________
void HTHiRACsIArray::Clear()
{
   for (int NumCsI = 0; NumCsI < fNumCsI; NumCsI++) {
      fHiRACsI[NumCsI]->Clear();
   }
}

//________________________________________________
int HTHiRACsIArray::GetNumCsI() const
{
   return fNumCsI;
}

//________________________________________________
HTHiRACsI *HTHiRACsIArray::GetCsI(int num_csi) const
{
   return fHiRACsI[num_csi];
}
