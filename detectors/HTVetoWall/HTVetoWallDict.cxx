// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTVetoWallDict

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
#include "HTVetoWallRootEvent.h"
#include "HTVetoWall.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_HTVetoWallData(void *p);
   static void deleteArray_HTVetoWallData(void *p);
   static void destruct_HTVetoWallData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTVetoWallData*)
   {
      ::HTVetoWallData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTVetoWallData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTVetoWallData", ::HTVetoWallData::Class_Version(), "HTVetoWallRootEvent.h", 6,
                  typeid(::HTVetoWallData), DefineBehavior(ptr, ptr),
                  &::HTVetoWallData::Dictionary, isa_proxy, 4,
                  sizeof(::HTVetoWallData) );
      instance.SetDelete(&delete_HTVetoWallData);
      instance.SetDeleteArray(&deleteArray_HTVetoWallData);
      instance.SetDestructor(&destruct_HTVetoWallData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTVetoWallData*)
   {
      return GenerateInitInstanceLocal((::HTVetoWallData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTVetoWallData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HTVetoWallRootEvent(void *p);
   static void deleteArray_HTVetoWallRootEvent(void *p);
   static void destruct_HTVetoWallRootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTVetoWallRootEvent*)
   {
      ::HTVetoWallRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTVetoWallRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTVetoWallRootEvent", ::HTVetoWallRootEvent::Class_Version(), "HTVetoWallRootEvent.h", 16,
                  typeid(::HTVetoWallRootEvent), DefineBehavior(ptr, ptr),
                  &::HTVetoWallRootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTVetoWallRootEvent) );
      instance.SetDelete(&delete_HTVetoWallRootEvent);
      instance.SetDeleteArray(&deleteArray_HTVetoWallRootEvent);
      instance.SetDestructor(&destruct_HTVetoWallRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTVetoWallRootEvent*)
   {
      return GenerateInitInstanceLocal((::HTVetoWallRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HTVetoWallRootEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTVetoWallData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTVetoWallData::Class_Name()
{
   return "HTVetoWallData";
}

//______________________________________________________________________________
const char *HTVetoWallData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTVetoWallData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTVetoWallData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTVetoWallData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTVetoWallRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTVetoWallRootEvent::Class_Name()
{
   return "HTVetoWallRootEvent";
}

//______________________________________________________________________________
const char *HTVetoWallRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTVetoWallRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTVetoWallRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTVetoWallRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTVetoWallRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTVetoWallData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTVetoWallData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTVetoWallData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTVetoWallData::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTVetoWallData(void *p) {
      delete ((::HTVetoWallData*)p);
   }
   static void deleteArray_HTVetoWallData(void *p) {
      delete [] ((::HTVetoWallData*)p);
   }
   static void destruct_HTVetoWallData(void *p) {
      typedef ::HTVetoWallData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTVetoWallData

//______________________________________________________________________________
void HTVetoWallRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTVetoWallRootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTVetoWallRootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTVetoWallRootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTVetoWallRootEvent(void *p) {
      delete ((::HTVetoWallRootEvent*)p);
   }
   static void deleteArray_HTVetoWallRootEvent(void *p) {
      delete [] ((::HTVetoWallRootEvent*)p);
   }
   static void destruct_HTVetoWallRootEvent(void *p) {
      typedef ::HTVetoWallRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTVetoWallRootEvent

namespace {
  void TriggerDictionaryInitialization_HTVetoWallDict_Impl() {
    static const char* headers[] = {
"HTVetoWallRootEvent.h",
"HTVetoWall.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/HTRootElectronics",
"/projects/hira/Daniele/HiRAEVT/HTDetectorMap",
"/projects/hira/Daniele/HiRAEVT/detectors/HTDetector",
"/projects/hira/Daniele/HiRAEVT/detectors/HTVetoWall",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/detectors/HTVetoWall/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HTVetoWallRootEvent.h")))  HTVetoWallData;
class __attribute__((annotate("$clingAutoload$HTVetoWallRootEvent.h")))  HTVetoWallRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HTVetoWallRootEvent.h"
#include "HTVetoWall.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HTVetoWallData", payloadCode, "@",
"HTVetoWallRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTVetoWallDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTVetoWallDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTVetoWallDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTVetoWallDict() {
  TriggerDictionaryInitialization_HTVetoWallDict_Impl();
}
