//
//  HTElectronics.h
//
//
//  Created by Andrew Rogers on 3/20/15.
//  Modified by Juan Manfredi
//

#ifndef HTMODULEUNPACKER
#define HTMODULEUNPACKER

#include "HTRootModule.h"

#include <TObject.h>
#include <TTree.h>
#include <iostream>
#include <stdio.h>

class HTModuleUnpacker : public TObject {
protected:
   Int_t fGeo;            // Module slot number or geographical address.
   UShort_t fUnpackError; // Unpacking error code.
   Int_t fUnpackErrorCount;

   std::shared_ptr<HTRootModule> fModule; // The ROOT version of the module to store in the tree.

   static ULong_t getLong(std::vector<UShort_t> &event, ULong_t offset);
   void PrintHex(std::vector<UShort_t> &event, ULong_t offset, ULong_t numbeWords, Int_t wordsPerLine = 8);

public:
   virtual ~HTModuleUnpacker(){};

   virtual Int_t Unpack(std::vector<UShort_t> &event, UInt_t offset) = 0;
   virtual Int_t DecodeVSN(Int_t header) = 0;

   virtual void PrintSummary() = 0;
   virtual void Print() { std::cout << fModule->GetName() << std::endl; }

   // Getters
   Int_t GetVSN() { return fGeo; }
   UShort_t GetUnpackError() { return fUnpackError; }
   Int_t GetUnpackErrorCount() { return fUnpackErrorCount; }
   std::shared_ptr<HTRootModule> GetRootModule() { return fModule; }
   
   // Setters
   void SetVSN(Int_t vsn) { fGeo = vsn; }
   void SetUnpackError(UShort_t code) { fUnpackError = code; } //

   ClassDef(HTModuleUnpacker, 1);
};
#endif /* defined(____HTElectronics__) */
