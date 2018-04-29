// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTHiRADict

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
#include "HTHiRA.h"
#include "HTHiRARootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_HTHiRAData(void *p);
   static void deleteArray_HTHiRAData(void *p);
   static void destruct_HTHiRAData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTHiRAData*)
   {
      ::HTHiRAData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTHiRAData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTHiRAData", ::HTHiRAData::Class_Version(), "HTHiRARootEvent.h", 6,
                  typeid(::HTHiRAData), DefineBehavior(ptr, ptr),
                  &::HTHiRAData::Dictionary, isa_proxy, 4,
                  sizeof(::HTHiRAData) );
      instance.SetDelete(&delete_HTHiRAData);
      instance.SetDeleteArray(&deleteArray_HTHiRAData);
      instance.SetDestructor(&destruct_HTHiRAData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTHiRAData*)
   {
      return GenerateInitInstanceLocal((::HTHiRAData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTHiRAData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HTHiRARootEvent(void *p);
   static void deleteArray_HTHiRARootEvent(void *p);
   static void destruct_HTHiRARootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTHiRARootEvent*)
   {
      ::HTHiRARootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTHiRARootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTHiRARootEvent", ::HTHiRARootEvent::Class_Version(), "HTHiRARootEvent.h", 16,
                  typeid(::HTHiRARootEvent), DefineBehavior(ptr, ptr),
                  &::HTHiRARootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTHiRARootEvent) );
      instance.SetDelete(&delete_HTHiRARootEvent);
      instance.SetDeleteArray(&deleteArray_HTHiRARootEvent);
      instance.SetDestructor(&destruct_HTHiRARootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTHiRARootEvent*)
   {
      return GenerateInitInstanceLocal((::HTHiRARootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTHiRARootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTHiRAData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTHiRAData::Class_Name()
{
   return "HTHiRAData";
}

//______________________________________________________________________________
const char *HTHiRAData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTHiRAData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTHiRAData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTHiRAData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTHiRAData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTHiRAData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTHiRAData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTHiRAData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTHiRARootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTHiRARootEvent::Class_Name()
{
   return "HTHiRARootEvent";
}

//______________________________________________________________________________
const char *HTHiRARootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTHiRARootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTHiRARootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTHiRARootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTHiRARootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTHiRARootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTHiRARootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTHiRARootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTHiRAData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTHiRAData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTHiRAData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTHiRAData::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTHiRAData(void *p) {
      delete ((::HTHiRAData*)p);
   }
   static void deleteArray_HTHiRAData(void *p) {
      delete [] ((::HTHiRAData*)p);
   }
   static void destruct_HTHiRAData(void *p) {
      typedef ::HTHiRAData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTHiRAData

//______________________________________________________________________________
void HTHiRARootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTHiRARootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTHiRARootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTHiRARootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTHiRARootEvent(void *p) {
      delete ((::HTHiRARootEvent*)p);
   }
   static void deleteArray_HTHiRARootEvent(void *p) {
      delete [] ((::HTHiRARootEvent*)p);
   }
   static void destruct_HTHiRARootEvent(void *p) {
      typedef ::HTHiRARootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTHiRARootEvent

namespace {
  void TriggerDictionaryInitialization_HTHiRADict_Impl() {
    static const char* headers[] = {
"HTHiRA.h",
"HTHiRARootEvent.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/electronics",
"/projects/hira/Daniele/HiRAEVT/HTRootElectronics",
"/projects/hira/Daniele/HiRAEVT/HTDetectorMap",
"/projects/hira/Daniele/HiRAEVT/detectors/HTDetector",
"/projects/hira/Daniele/HiRAEVT/detectors/HTHiRA",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/detectors/HTHiRA/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HTHiRA.h")))  HTHiRAData;
class __attribute__((annotate("$clingAutoload$HTHiRA.h")))  HTHiRARootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HTHiRA.h"
#include "HTHiRARootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HTHiRAData", payloadCode, "@",
"HTHiRARootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTHiRADict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTHiRADict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTHiRADict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTHiRADict() {
  TriggerDictionaryInitialization_HTHiRADict_Impl();
}
