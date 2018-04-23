// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RBExperimentDict

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
#include "RBExperiment.h"
#include "RBRingItem.h"
#include "RBNSCLBufferHeader.h"
#include "RBRingStateChangeItem.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RBRingItem(void *p = 0);
   static void *newArray_RBRingItem(Long_t size, void *p);
   static void delete_RBRingItem(void *p);
   static void deleteArray_RBRingItem(void *p);
   static void destruct_RBRingItem(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBRingItem*)
   {
      ::RBRingItem *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBRingItem >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBRingItem", ::RBRingItem::Class_Version(), "RBRingItem.h", 20,
                  typeid(::RBRingItem), DefineBehavior(ptr, ptr),
                  &::RBRingItem::Dictionary, isa_proxy, 4,
                  sizeof(::RBRingItem) );
      instance.SetNew(&new_RBRingItem);
      instance.SetNewArray(&newArray_RBRingItem);
      instance.SetDelete(&delete_RBRingItem);
      instance.SetDeleteArray(&deleteArray_RBRingItem);
      instance.SetDestructor(&destruct_RBRingItem);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBRingItem*)
   {
      return GenerateInitInstanceLocal((::RBRingItem*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBRingItem*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBRingStateChangeItem(void *p = 0);
   static void *newArray_RBRingStateChangeItem(Long_t size, void *p);
   static void delete_RBRingStateChangeItem(void *p);
   static void deleteArray_RBRingStateChangeItem(void *p);
   static void destruct_RBRingStateChangeItem(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBRingStateChangeItem*)
   {
      ::RBRingStateChangeItem *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBRingStateChangeItem >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBRingStateChangeItem", ::RBRingStateChangeItem::Class_Version(), "RBRingStateChangeItem.h", 24,
                  typeid(::RBRingStateChangeItem), DefineBehavior(ptr, ptr),
                  &::RBRingStateChangeItem::Dictionary, isa_proxy, 4,
                  sizeof(::RBRingStateChangeItem) );
      instance.SetNew(&new_RBRingStateChangeItem);
      instance.SetNewArray(&newArray_RBRingStateChangeItem);
      instance.SetDelete(&delete_RBRingStateChangeItem);
      instance.SetDeleteArray(&deleteArray_RBRingStateChangeItem);
      instance.SetDestructor(&destruct_RBRingStateChangeItem);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBRingStateChangeItem*)
   {
      return GenerateInitInstanceLocal((::RBRingStateChangeItem*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBRingStateChangeItem*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBNSCLBufferHeader(void *p = 0);
   static void *newArray_RBNSCLBufferHeader(Long_t size, void *p);
   static void delete_RBNSCLBufferHeader(void *p);
   static void deleteArray_RBNSCLBufferHeader(void *p);
   static void destruct_RBNSCLBufferHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBNSCLBufferHeader*)
   {
      ::RBNSCLBufferHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBNSCLBufferHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBNSCLBufferHeader", ::RBNSCLBufferHeader::Class_Version(), "RBNSCLBufferHeader.h", 20,
                  typeid(::RBNSCLBufferHeader), DefineBehavior(ptr, ptr),
                  &::RBNSCLBufferHeader::Dictionary, isa_proxy, 4,
                  sizeof(::RBNSCLBufferHeader) );
      instance.SetNew(&new_RBNSCLBufferHeader);
      instance.SetNewArray(&newArray_RBNSCLBufferHeader);
      instance.SetDelete(&delete_RBNSCLBufferHeader);
      instance.SetDeleteArray(&deleteArray_RBNSCLBufferHeader);
      instance.SetDestructor(&destruct_RBNSCLBufferHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBNSCLBufferHeader*)
   {
      return GenerateInitInstanceLocal((::RBNSCLBufferHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBNSCLBufferHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBExperiment(void *p = 0);
   static void *newArray_RBExperiment(Long_t size, void *p);
   static void delete_RBExperiment(void *p);
   static void deleteArray_RBExperiment(void *p);
   static void destruct_RBExperiment(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBExperiment*)
   {
      ::RBExperiment *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBExperiment >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBExperiment", ::RBExperiment::Class_Version(), "RBExperiment.h", 36,
                  typeid(::RBExperiment), DefineBehavior(ptr, ptr),
                  &::RBExperiment::Dictionary, isa_proxy, 4,
                  sizeof(::RBExperiment) );
      instance.SetNew(&new_RBExperiment);
      instance.SetNewArray(&newArray_RBExperiment);
      instance.SetDelete(&delete_RBExperiment);
      instance.SetDeleteArray(&deleteArray_RBExperiment);
      instance.SetDestructor(&destruct_RBExperiment);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBExperiment*)
   {
      return GenerateInitInstanceLocal((::RBExperiment*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBExperiment*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RBRingItem::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBRingItem::Class_Name()
{
   return "RBRingItem";
}

//______________________________________________________________________________
const char *RBRingItem::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBRingItem*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBRingItem::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBRingItem*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBRingItem::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBRingItem*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBRingItem::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBRingItem*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBRingStateChangeItem::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBRingStateChangeItem::Class_Name()
{
   return "RBRingStateChangeItem";
}

//______________________________________________________________________________
const char *RBRingStateChangeItem::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBRingStateChangeItem*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBRingStateChangeItem::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBRingStateChangeItem*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBRingStateChangeItem::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBRingStateChangeItem*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBRingStateChangeItem::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBRingStateChangeItem*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBNSCLBufferHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBNSCLBufferHeader::Class_Name()
{
   return "RBNSCLBufferHeader";
}

//______________________________________________________________________________
const char *RBNSCLBufferHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBNSCLBufferHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBNSCLBufferHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBNSCLBufferHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBNSCLBufferHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBNSCLBufferHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBNSCLBufferHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBNSCLBufferHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBExperiment::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBExperiment::Class_Name()
{
   return "RBExperiment";
}

//______________________________________________________________________________
const char *RBExperiment::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBExperiment*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBExperiment::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBExperiment*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBExperiment::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBExperiment*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBExperiment::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBExperiment*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RBRingItem::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBRingItem.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBRingItem::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBRingItem::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBRingItem(void *p) {
      return  p ? new(p) ::RBRingItem : new ::RBRingItem;
   }
   static void *newArray_RBRingItem(Long_t nElements, void *p) {
      return p ? new(p) ::RBRingItem[nElements] : new ::RBRingItem[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBRingItem(void *p) {
      delete ((::RBRingItem*)p);
   }
   static void deleteArray_RBRingItem(void *p) {
      delete [] ((::RBRingItem*)p);
   }
   static void destruct_RBRingItem(void *p) {
      typedef ::RBRingItem current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBRingItem

//______________________________________________________________________________
void RBRingStateChangeItem::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBRingStateChangeItem.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBRingStateChangeItem::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBRingStateChangeItem::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBRingStateChangeItem(void *p) {
      return  p ? new(p) ::RBRingStateChangeItem : new ::RBRingStateChangeItem;
   }
   static void *newArray_RBRingStateChangeItem(Long_t nElements, void *p) {
      return p ? new(p) ::RBRingStateChangeItem[nElements] : new ::RBRingStateChangeItem[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBRingStateChangeItem(void *p) {
      delete ((::RBRingStateChangeItem*)p);
   }
   static void deleteArray_RBRingStateChangeItem(void *p) {
      delete [] ((::RBRingStateChangeItem*)p);
   }
   static void destruct_RBRingStateChangeItem(void *p) {
      typedef ::RBRingStateChangeItem current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBRingStateChangeItem

//______________________________________________________________________________
void RBNSCLBufferHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBNSCLBufferHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBNSCLBufferHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBNSCLBufferHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBNSCLBufferHeader(void *p) {
      return  p ? new(p) ::RBNSCLBufferHeader : new ::RBNSCLBufferHeader;
   }
   static void *newArray_RBNSCLBufferHeader(Long_t nElements, void *p) {
      return p ? new(p) ::RBNSCLBufferHeader[nElements] : new ::RBNSCLBufferHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBNSCLBufferHeader(void *p) {
      delete ((::RBNSCLBufferHeader*)p);
   }
   static void deleteArray_RBNSCLBufferHeader(void *p) {
      delete [] ((::RBNSCLBufferHeader*)p);
   }
   static void destruct_RBNSCLBufferHeader(void *p) {
      typedef ::RBNSCLBufferHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBNSCLBufferHeader

//______________________________________________________________________________
void RBExperiment::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBExperiment.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBExperiment::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBExperiment::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBExperiment(void *p) {
      return  p ? new(p) ::RBExperiment : new ::RBExperiment;
   }
   static void *newArray_RBExperiment(Long_t nElements, void *p) {
      return p ? new(p) ::RBExperiment[nElements] : new ::RBExperiment[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBExperiment(void *p) {
      delete ((::RBExperiment*)p);
   }
   static void deleteArray_RBExperiment(void *p) {
      delete [] ((::RBExperiment*)p);
   }
   static void destruct_RBExperiment(void *p) {
      typedef ::RBExperiment current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBExperiment

namespace {
  void TriggerDictionaryInitialization_RBExperimentDict_Impl() {
    static const char* headers[] = {
"RBExperiment.h",
"RBRingItem.h",
"RBNSCLBufferHeader.h",
"RBRingStateChangeItem.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT//",
"/projects/hira/Daniele/HiRAEVT//electronics",
"/projects/hira/Daniele/HiRAEVT//shared",
"/projects/hira/Daniele/HiRAEVT//RBRunInfo",
"/projects/hira/Daniele/HiRAEVT//RBExperiment",
"/projects/hira/Daniele/HiRAEVT//FilterUnpacker",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/RBExperiment/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$RBExperiment.h")))  RBRingItem;
class __attribute__((annotate("$clingAutoload$RBExperiment.h")))  RBRingStateChangeItem;
class __attribute__((annotate("$clingAutoload$RBExperiment.h")))  RBNSCLBufferHeader;
class __attribute__((annotate(R"ATTRDUMP(NSCL event-data unpacker.)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$RBExperiment.h")))  RBExperiment;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RBExperiment.h"
#include "RBRingItem.h"
#include "RBNSCLBufferHeader.h"
#include "RBRingStateChangeItem.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RBExperiment", payloadCode, "@",
"RBNSCLBufferHeader", payloadCode, "@",
"RBRingItem", payloadCode, "@",
"RBRingStateChangeItem", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RBExperimentDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RBExperimentDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RBExperimentDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RBExperimentDict() {
  TriggerDictionaryInitialization_RBExperimentDict_Impl();
}
