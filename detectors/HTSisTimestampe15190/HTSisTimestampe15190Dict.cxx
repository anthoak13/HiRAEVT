// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTSisTimestampe15190Dict

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
#include "HTSisTimestampe15190.h"
#include "HTTSe15190RootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_HTTSe15190Data(void *p = 0);
   static void *newArray_HTTSe15190Data(Long_t size, void *p);
   static void delete_HTTSe15190Data(void *p);
   static void deleteArray_HTTSe15190Data(void *p);
   static void destruct_HTTSe15190Data(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTTSe15190Data*)
   {
      ::HTTSe15190Data *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTTSe15190Data >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTTSe15190Data", ::HTTSe15190Data::Class_Version(), "HTTSe15190RootEvent.h", 6,
                  typeid(::HTTSe15190Data), DefineBehavior(ptr, ptr),
                  &::HTTSe15190Data::Dictionary, isa_proxy, 4,
                  sizeof(::HTTSe15190Data) );
      instance.SetNew(&new_HTTSe15190Data);
      instance.SetNewArray(&newArray_HTTSe15190Data);
      instance.SetDelete(&delete_HTTSe15190Data);
      instance.SetDeleteArray(&deleteArray_HTTSe15190Data);
      instance.SetDestructor(&destruct_HTTSe15190Data);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTTSe15190Data*)
   {
      return GenerateInitInstanceLocal((::HTTSe15190Data*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTTSe15190Data*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HTTSe15190RootEvent(void *p = 0);
   static void *newArray_HTTSe15190RootEvent(Long_t size, void *p);
   static void delete_HTTSe15190RootEvent(void *p);
   static void deleteArray_HTTSe15190RootEvent(void *p);
   static void destruct_HTTSe15190RootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTTSe15190RootEvent*)
   {
      ::HTTSe15190RootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTTSe15190RootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTTSe15190RootEvent", ::HTTSe15190RootEvent::Class_Version(), "HTTSe15190RootEvent.h", 18,
                  typeid(::HTTSe15190RootEvent), DefineBehavior(ptr, ptr),
                  &::HTTSe15190RootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTTSe15190RootEvent) );
      instance.SetNew(&new_HTTSe15190RootEvent);
      instance.SetNewArray(&newArray_HTTSe15190RootEvent);
      instance.SetDelete(&delete_HTTSe15190RootEvent);
      instance.SetDeleteArray(&deleteArray_HTTSe15190RootEvent);
      instance.SetDestructor(&destruct_HTTSe15190RootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTTSe15190RootEvent*)
   {
      return GenerateInitInstanceLocal((::HTTSe15190RootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTTSe15190RootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTTSe15190Data::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTTSe15190Data::Class_Name()
{
   return "HTTSe15190Data";
}

//______________________________________________________________________________
const char *HTTSe15190Data::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190Data*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTTSe15190Data::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190Data*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTTSe15190Data::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190Data*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTTSe15190Data::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190Data*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTTSe15190RootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTTSe15190RootEvent::Class_Name()
{
   return "HTTSe15190RootEvent";
}

//______________________________________________________________________________
const char *HTTSe15190RootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190RootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTTSe15190RootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190RootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTTSe15190RootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190RootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTTSe15190RootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTTSe15190RootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTTSe15190Data::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTTSe15190Data.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTTSe15190Data::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTTSe15190Data::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HTTSe15190Data(void *p) {
      return  p ? new(p) ::HTTSe15190Data : new ::HTTSe15190Data;
   }
   static void *newArray_HTTSe15190Data(Long_t nElements, void *p) {
      return p ? new(p) ::HTTSe15190Data[nElements] : new ::HTTSe15190Data[nElements];
   }
   // Wrapper around operator delete
   static void delete_HTTSe15190Data(void *p) {
      delete ((::HTTSe15190Data*)p);
   }
   static void deleteArray_HTTSe15190Data(void *p) {
      delete [] ((::HTTSe15190Data*)p);
   }
   static void destruct_HTTSe15190Data(void *p) {
      typedef ::HTTSe15190Data current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTTSe15190Data

//______________________________________________________________________________
void HTTSe15190RootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTTSe15190RootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTTSe15190RootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTTSe15190RootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HTTSe15190RootEvent(void *p) {
      return  p ? new(p) ::HTTSe15190RootEvent : new ::HTTSe15190RootEvent;
   }
   static void *newArray_HTTSe15190RootEvent(Long_t nElements, void *p) {
      return p ? new(p) ::HTTSe15190RootEvent[nElements] : new ::HTTSe15190RootEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_HTTSe15190RootEvent(void *p) {
      delete ((::HTTSe15190RootEvent*)p);
   }
   static void deleteArray_HTTSe15190RootEvent(void *p) {
      delete [] ((::HTTSe15190RootEvent*)p);
   }
   static void destruct_HTTSe15190RootEvent(void *p) {
      typedef ::HTTSe15190RootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTTSe15190RootEvent

namespace {
  void TriggerDictionaryInitialization_HTSisTimestampe15190Dict_Impl() {
    static const char* headers[] = {
"HTSisTimestampe15190.h",
"HTTSe15190RootEvent.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/HTRootElectronics",
"/projects/hira/Daniele/HiRAEVT/HTDetectorMap",
"/projects/hira/Daniele/HiRAEVT/detectors/HTDetector",
"/projects/hira/Daniele/HiRAEVT/detectors/HTSisTimestampe15190",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/detectors/HTSisTimestampe15190/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HTSisTimestampe15190.h")))  HTTSe15190Data;
class __attribute__((annotate("$clingAutoload$HTSisTimestampe15190.h")))  HTTSe15190RootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HTSisTimestampe15190.h"
#include "HTTSe15190RootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HTTSe15190Data", payloadCode, "@",
"HTTSe15190RootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTSisTimestampe15190Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTSisTimestampe15190Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTSisTimestampe15190Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTSisTimestampe15190Dict() {
  TriggerDictionaryInitialization_HTSisTimestampe15190Dict_Impl();
}
