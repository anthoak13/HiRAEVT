// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTForwardArrayDict

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
#include "HTForwardArrayDetector.h"
#include "HTForwardArray.h"
#include "HTForwardArrayRootEvent.h"
#include "HTForwardArrayCluster.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_HTForwardArrayData(void *p);
   static void deleteArray_HTForwardArrayData(void *p);
   static void destruct_HTForwardArrayData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTForwardArrayData*)
   {
      ::HTForwardArrayData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTForwardArrayData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTForwardArrayData", ::HTForwardArrayData::Class_Version(), "HTForwardArrayRootEvent.h", 6,
                  typeid(::HTForwardArrayData), DefineBehavior(ptr, ptr),
                  &::HTForwardArrayData::Dictionary, isa_proxy, 4,
                  sizeof(::HTForwardArrayData) );
      instance.SetDelete(&delete_HTForwardArrayData);
      instance.SetDeleteArray(&deleteArray_HTForwardArrayData);
      instance.SetDestructor(&destruct_HTForwardArrayData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTForwardArrayData*)
   {
      return GenerateInitInstanceLocal((::HTForwardArrayData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTForwardArrayData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HTForwardArrayRootEvent(void *p);
   static void deleteArray_HTForwardArrayRootEvent(void *p);
   static void destruct_HTForwardArrayRootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTForwardArrayRootEvent*)
   {
      ::HTForwardArrayRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTForwardArrayRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTForwardArrayRootEvent", ::HTForwardArrayRootEvent::Class_Version(), "HTForwardArrayRootEvent.h", 20,
                  typeid(::HTForwardArrayRootEvent), DefineBehavior(ptr, ptr),
                  &::HTForwardArrayRootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTForwardArrayRootEvent) );
      instance.SetDelete(&delete_HTForwardArrayRootEvent);
      instance.SetDeleteArray(&deleteArray_HTForwardArrayRootEvent);
      instance.SetDestructor(&destruct_HTForwardArrayRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTForwardArrayRootEvent*)
   {
      return GenerateInitInstanceLocal((::HTForwardArrayRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTForwardArrayRootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTForwardArrayData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTForwardArrayData::Class_Name()
{
   return "HTForwardArrayData";
}

//______________________________________________________________________________
const char *HTForwardArrayData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTForwardArrayData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTForwardArrayData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTForwardArrayData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTForwardArrayRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTForwardArrayRootEvent::Class_Name()
{
   return "HTForwardArrayRootEvent";
}

//______________________________________________________________________________
const char *HTForwardArrayRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTForwardArrayRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTForwardArrayRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTForwardArrayRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTForwardArrayRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTForwardArrayData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTForwardArrayData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTForwardArrayData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTForwardArrayData::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTForwardArrayData(void *p) {
      delete ((::HTForwardArrayData*)p);
   }
   static void deleteArray_HTForwardArrayData(void *p) {
      delete [] ((::HTForwardArrayData*)p);
   }
   static void destruct_HTForwardArrayData(void *p) {
      typedef ::HTForwardArrayData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTForwardArrayData

//______________________________________________________________________________
void HTForwardArrayRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTForwardArrayRootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTForwardArrayRootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTForwardArrayRootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTForwardArrayRootEvent(void *p) {
      delete ((::HTForwardArrayRootEvent*)p);
   }
   static void deleteArray_HTForwardArrayRootEvent(void *p) {
      delete [] ((::HTForwardArrayRootEvent*)p);
   }
   static void destruct_HTForwardArrayRootEvent(void *p) {
      typedef ::HTForwardArrayRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTForwardArrayRootEvent

namespace {
  void TriggerDictionaryInitialization_HTForwardArrayDict_Impl() {
    static const char* headers[] = {
"HTForwardArrayDetector.h",
"HTForwardArray.h",
"HTForwardArrayRootEvent.h",
"HTForwardArrayCluster.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/HTRootElectronics",
"/projects/hira/Daniele/HiRAEVT/HTDetectorMap",
"/projects/hira/Daniele/HiRAEVT/detectors/HTDetector",
"/projects/hira/Daniele/HiRAEVT/detectors/HTForwardArray",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/detectors/HTForwardArray/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HTForwardArray.h")))  HTForwardArrayData;
class __attribute__((annotate("$clingAutoload$HTForwardArray.h")))  HTForwardArrayRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HTForwardArrayDetector.h"
#include "HTForwardArray.h"
#include "HTForwardArrayRootEvent.h"
#include "HTForwardArrayCluster.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HTForwardArrayData", payloadCode, "@",
"HTForwardArrayRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTForwardArrayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTForwardArrayDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTForwardArrayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTForwardArrayDict() {
  TriggerDictionaryInitialization_HTForwardArrayDict_Impl();
}
