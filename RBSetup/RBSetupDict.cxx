// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RBSetupDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "RBSetup.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RBSetup(void *p = 0);
   static void *newArray_RBSetup(Long_t size, void *p);
   static void delete_RBSetup(void *p);
   static void deleteArray_RBSetup(void *p);
   static void destruct_RBSetup(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBSetup*)
   {
      ::RBSetup *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBSetup >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBSetup", ::RBSetup::Class_Version(), "RBSetup.h", 11,
                  typeid(::RBSetup), DefineBehavior(ptr, ptr),
                  &::RBSetup::Dictionary, isa_proxy, 4,
                  sizeof(::RBSetup) );
      instance.SetNew(&new_RBSetup);
      instance.SetNewArray(&newArray_RBSetup);
      instance.SetDelete(&delete_RBSetup);
      instance.SetDeleteArray(&deleteArray_RBSetup);
      instance.SetDestructor(&destruct_RBSetup);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBSetup*)
   {
      return GenerateInitInstanceLocal((::RBSetup*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBSetup*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RBSetup::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBSetup::Class_Name()
{
   return "RBSetup";
}

//______________________________________________________________________________
const char *RBSetup::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBSetup::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBSetup::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBSetup::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RBSetup::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBSetup.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBSetup::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBSetup::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBSetup(void *p) {
      return  p ? new(p) ::RBSetup : new ::RBSetup;
   }
   static void *newArray_RBSetup(Long_t nElements, void *p) {
      return p ? new(p) ::RBSetup[nElements] : new ::RBSetup[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBSetup(void *p) {
      delete ((::RBSetup*)p);
   }
   static void deleteArray_RBSetup(void *p) {
      delete [] ((::RBSetup*)p);
   }
   static void destruct_RBSetup(void *p) {
      typedef ::RBSetup current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBSetup

namespace {
  void TriggerDictionaryInitialization_RBSetupDict_Impl() {
    static const char* headers[] = {
"RBSetup.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT//",
"/projects/hira/Daniele/HiRAEVT//electronics",
"/projects/hira/Daniele/HiRAEVT//shared",
"/projects/hira/Daniele/HiRAEVT//HTRunInfo",
"/projects/hira/Daniele/HiRAEVT//RBSetup",
"/projects/hira/Daniele/HiRAEVT//RBExperiment",
"/projects/hira/Daniele/HiRAEVT//FilterUnpacker",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/RBSetup/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$RBSetup.h")))  RBSetup;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RBSetup.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RBSetup", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RBSetupDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RBSetupDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RBSetupDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RBSetupDict() {
  TriggerDictionaryInitialization_RBSetupDict_Impl();
}
