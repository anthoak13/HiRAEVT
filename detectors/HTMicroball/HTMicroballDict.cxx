// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTMicroballDict

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
#include "HTMicroballRootEvent.h"
#include "HTMicroballArray.h"
#include "HTMicroballRing.h"
#include "HTMicroball.h"
#include "HTMicroballDetector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_HTMicroballData(void *p);
   static void deleteArray_HTMicroballData(void *p);
   static void destruct_HTMicroballData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTMicroballData*)
   {
      ::HTMicroballData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTMicroballData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTMicroballData", ::HTMicroballData::Class_Version(), "HTMicroballRootEvent.h", 6,
                  typeid(::HTMicroballData), DefineBehavior(ptr, ptr),
                  &::HTMicroballData::Dictionary, isa_proxy, 4,
                  sizeof(::HTMicroballData) );
      instance.SetDelete(&delete_HTMicroballData);
      instance.SetDeleteArray(&deleteArray_HTMicroballData);
      instance.SetDestructor(&destruct_HTMicroballData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTMicroballData*)
   {
      return GenerateInitInstanceLocal((::HTMicroballData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTMicroballData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HTMicroballRootEvent(void *p);
   static void deleteArray_HTMicroballRootEvent(void *p);
   static void destruct_HTMicroballRootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTMicroballRootEvent*)
   {
      ::HTMicroballRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTMicroballRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTMicroballRootEvent", ::HTMicroballRootEvent::Class_Version(), "HTMicroballRootEvent.h", 22,
                  typeid(::HTMicroballRootEvent), DefineBehavior(ptr, ptr),
                  &::HTMicroballRootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTMicroballRootEvent) );
      instance.SetDelete(&delete_HTMicroballRootEvent);
      instance.SetDeleteArray(&deleteArray_HTMicroballRootEvent);
      instance.SetDestructor(&destruct_HTMicroballRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTMicroballRootEvent*)
   {
      return GenerateInitInstanceLocal((::HTMicroballRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTMicroballRootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTMicroballData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTMicroballData::Class_Name()
{
   return "HTMicroballData";
}

//______________________________________________________________________________
const char *HTMicroballData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTMicroballData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTMicroballData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTMicroballData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTMicroballRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTMicroballRootEvent::Class_Name()
{
   return "HTMicroballRootEvent";
}

//______________________________________________________________________________
const char *HTMicroballRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTMicroballRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTMicroballRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTMicroballRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTMicroballRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTMicroballData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTMicroballData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTMicroballData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTMicroballData::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTMicroballData(void *p) {
      delete ((::HTMicroballData*)p);
   }
   static void deleteArray_HTMicroballData(void *p) {
      delete [] ((::HTMicroballData*)p);
   }
   static void destruct_HTMicroballData(void *p) {
      typedef ::HTMicroballData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTMicroballData

//______________________________________________________________________________
void HTMicroballRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTMicroballRootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTMicroballRootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTMicroballRootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTMicroballRootEvent(void *p) {
      delete ((::HTMicroballRootEvent*)p);
   }
   static void deleteArray_HTMicroballRootEvent(void *p) {
      delete [] ((::HTMicroballRootEvent*)p);
   }
   static void destruct_HTMicroballRootEvent(void *p) {
      typedef ::HTMicroballRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTMicroballRootEvent

namespace {
  void TriggerDictionaryInitialization_HTMicroballDict_Impl() {
    static const char* headers[] = {
"HTMicroballRootEvent.h",
"HTMicroballArray.h",
"HTMicroballRing.h",
"HTMicroball.h",
"HTMicroballDetector.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/HTRootElectronics",
"/projects/hira/Daniele/HiRAEVT/HTDetectorMap",
"/projects/hira/Daniele/HiRAEVT/detectors/HTDetector",
"/projects/hira/Daniele/HiRAEVT/detectors/HTMicroball",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/detectors/HTMicroball/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HTMicroballRootEvent.h")))  HTMicroballData;
class __attribute__((annotate("$clingAutoload$HTMicroballRootEvent.h")))  HTMicroballRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HTMicroballRootEvent.h"
#include "HTMicroballArray.h"
#include "HTMicroballRing.h"
#include "HTMicroball.h"
#include "HTMicroballDetector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HTMicroballData", payloadCode, "@",
"HTMicroballRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTMicroballDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTMicroballDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTMicroballDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTMicroballDict() {
  TriggerDictionaryInitialization_HTMicroballDict_Impl();
}
