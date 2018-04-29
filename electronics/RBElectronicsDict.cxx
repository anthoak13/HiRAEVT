// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RBElectronicsDict

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
#include "RBElectronics.h"
#include "RBSisTimestampUnpacker.h"
#include "RBHINPUnpacker.h"
#include "RBCCUSBPacket.h"
#include "RBPh7xxUnpacker.h"
#include "RBCAEN7xxUnpacker.h"
#include "RBUSBStackMarker.h"
#include "RBTimestamp.h"
#include "RBUSBStack.h"
#include "RBHINPHit.h"
#include "RBModuleUnpacker.h"
#include "RBCAEN1x90Unpacker.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_RBTimestamp(void *p);
   static void deleteArray_RBTimestamp(void *p);
   static void destruct_RBTimestamp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBTimestamp*)
   {
      ::RBTimestamp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBTimestamp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBTimestamp", ::RBTimestamp::Class_Version(), "RBTimestamp.h", 12,
                  typeid(::RBTimestamp), DefineBehavior(ptr, ptr),
                  &::RBTimestamp::Dictionary, isa_proxy, 4,
                  sizeof(::RBTimestamp) );
      instance.SetDelete(&delete_RBTimestamp);
      instance.SetDeleteArray(&deleteArray_RBTimestamp);
      instance.SetDestructor(&destruct_RBTimestamp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBTimestamp*)
   {
      return GenerateInitInstanceLocal((::RBTimestamp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBTimestamp*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_RBHINPUnpacker(void *p);
   static void deleteArray_RBHINPUnpacker(void *p);
   static void destruct_RBHINPUnpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBHINPUnpacker*)
   {
      ::RBHINPUnpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBHINPUnpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBHINPUnpacker", ::RBHINPUnpacker::Class_Version(), "RBHINPUnpacker.h", 14,
                  typeid(::RBHINPUnpacker), DefineBehavior(ptr, ptr),
                  &::RBHINPUnpacker::Dictionary, isa_proxy, 4,
                  sizeof(::RBHINPUnpacker) );
      instance.SetDelete(&delete_RBHINPUnpacker);
      instance.SetDeleteArray(&deleteArray_RBHINPUnpacker);
      instance.SetDestructor(&destruct_RBHINPUnpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBHINPUnpacker*)
   {
      return GenerateInitInstanceLocal((::RBHINPUnpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBHINPUnpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBHINPHit(void *p = 0);
   static void *newArray_RBHINPHit(Long_t size, void *p);
   static void delete_RBHINPHit(void *p);
   static void deleteArray_RBHINPHit(void *p);
   static void destruct_RBHINPHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBHINPHit*)
   {
      ::RBHINPHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBHINPHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBHINPHit", ::RBHINPHit::Class_Version(), "RBHINPHit.h", 6,
                  typeid(::RBHINPHit), DefineBehavior(ptr, ptr),
                  &::RBHINPHit::Dictionary, isa_proxy, 4,
                  sizeof(::RBHINPHit) );
      instance.SetNew(&new_RBHINPHit);
      instance.SetNewArray(&newArray_RBHINPHit);
      instance.SetDelete(&delete_RBHINPHit);
      instance.SetDeleteArray(&deleteArray_RBHINPHit);
      instance.SetDestructor(&destruct_RBHINPHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBHINPHit*)
   {
      return GenerateInitInstanceLocal((::RBHINPHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBHINPHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBCAEN7xxUnpacker(void *p = 0);
   static void *newArray_RBCAEN7xxUnpacker(Long_t size, void *p);
   static void delete_RBCAEN7xxUnpacker(void *p);
   static void deleteArray_RBCAEN7xxUnpacker(void *p);
   static void destruct_RBCAEN7xxUnpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBCAEN7xxUnpacker*)
   {
      ::RBCAEN7xxUnpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBCAEN7xxUnpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBCAEN7xxUnpacker", ::RBCAEN7xxUnpacker::Class_Version(), "RBCAEN7xxUnpacker.h", 25,
                  typeid(::RBCAEN7xxUnpacker), DefineBehavior(ptr, ptr),
                  &::RBCAEN7xxUnpacker::Dictionary, isa_proxy, 4,
                  sizeof(::RBCAEN7xxUnpacker) );
      instance.SetNew(&new_RBCAEN7xxUnpacker);
      instance.SetNewArray(&newArray_RBCAEN7xxUnpacker);
      instance.SetDelete(&delete_RBCAEN7xxUnpacker);
      instance.SetDeleteArray(&deleteArray_RBCAEN7xxUnpacker);
      instance.SetDestructor(&destruct_RBCAEN7xxUnpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBCAEN7xxUnpacker*)
   {
      return GenerateInitInstanceLocal((::RBCAEN7xxUnpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBCAEN7xxUnpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBCAEN1x90Unpacker(void *p = 0);
   static void *newArray_RBCAEN1x90Unpacker(Long_t size, void *p);
   static void delete_RBCAEN1x90Unpacker(void *p);
   static void deleteArray_RBCAEN1x90Unpacker(void *p);
   static void destruct_RBCAEN1x90Unpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBCAEN1x90Unpacker*)
   {
      ::RBCAEN1x90Unpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBCAEN1x90Unpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBCAEN1x90Unpacker", ::RBCAEN1x90Unpacker::Class_Version(), "RBCAEN1x90Unpacker.h", 21,
                  typeid(::RBCAEN1x90Unpacker), DefineBehavior(ptr, ptr),
                  &::RBCAEN1x90Unpacker::Dictionary, isa_proxy, 4,
                  sizeof(::RBCAEN1x90Unpacker) );
      instance.SetNew(&new_RBCAEN1x90Unpacker);
      instance.SetNewArray(&newArray_RBCAEN1x90Unpacker);
      instance.SetDelete(&delete_RBCAEN1x90Unpacker);
      instance.SetDeleteArray(&deleteArray_RBCAEN1x90Unpacker);
      instance.SetDestructor(&destruct_RBCAEN1x90Unpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBCAEN1x90Unpacker*)
   {
      return GenerateInitInstanceLocal((::RBCAEN1x90Unpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBCAEN1x90Unpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBPh7xxUnpacker(void *p = 0);
   static void *newArray_RBPh7xxUnpacker(Long_t size, void *p);
   static void delete_RBPh7xxUnpacker(void *p);
   static void deleteArray_RBPh7xxUnpacker(void *p);
   static void destruct_RBPh7xxUnpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBPh7xxUnpacker*)
   {
      ::RBPh7xxUnpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBPh7xxUnpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBPh7xxUnpacker", ::RBPh7xxUnpacker::Class_Version(), "RBPh7xxUnpacker.h", 28,
                  typeid(::RBPh7xxUnpacker), DefineBehavior(ptr, ptr),
                  &::RBPh7xxUnpacker::Dictionary, isa_proxy, 4,
                  sizeof(::RBPh7xxUnpacker) );
      instance.SetNew(&new_RBPh7xxUnpacker);
      instance.SetNewArray(&newArray_RBPh7xxUnpacker);
      instance.SetDelete(&delete_RBPh7xxUnpacker);
      instance.SetDeleteArray(&deleteArray_RBPh7xxUnpacker);
      instance.SetDestructor(&destruct_RBPh7xxUnpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBPh7xxUnpacker*)
   {
      return GenerateInitInstanceLocal((::RBPh7xxUnpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBPh7xxUnpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RBUSBStack(void *p = 0);
   static void *newArray_RBUSBStack(Long_t size, void *p);
   static void delete_RBUSBStack(void *p);
   static void deleteArray_RBUSBStack(void *p);
   static void destruct_RBUSBStack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBUSBStack*)
   {
      ::RBUSBStack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBUSBStack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBUSBStack", ::RBUSBStack::Class_Version(), "RBUSBStack.h", 29,
                  typeid(::RBUSBStack), DefineBehavior(ptr, ptr),
                  &::RBUSBStack::Dictionary, isa_proxy, 4,
                  sizeof(::RBUSBStack) );
      instance.SetNew(&new_RBUSBStack);
      instance.SetNewArray(&newArray_RBUSBStack);
      instance.SetDelete(&delete_RBUSBStack);
      instance.SetDeleteArray(&deleteArray_RBUSBStack);
      instance.SetDestructor(&destruct_RBUSBStack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBUSBStack*)
   {
      return GenerateInitInstanceLocal((::RBUSBStack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBUSBStack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_RBUSBStackMarker(void *p);
   static void deleteArray_RBUSBStackMarker(void *p);
   static void destruct_RBUSBStackMarker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBUSBStackMarker*)
   {
      ::RBUSBStackMarker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBUSBStackMarker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBUSBStackMarker", ::RBUSBStackMarker::Class_Version(), "RBUSBStackMarker.h", 12,
                  typeid(::RBUSBStackMarker), DefineBehavior(ptr, ptr),
                  &::RBUSBStackMarker::Dictionary, isa_proxy, 4,
                  sizeof(::RBUSBStackMarker) );
      instance.SetDelete(&delete_RBUSBStackMarker);
      instance.SetDeleteArray(&deleteArray_RBUSBStackMarker);
      instance.SetDestructor(&destruct_RBUSBStackMarker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBUSBStackMarker*)
   {
      return GenerateInitInstanceLocal((::RBUSBStackMarker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBUSBStackMarker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_RBElectronics(void *p);
   static void deleteArray_RBElectronics(void *p);
   static void destruct_RBElectronics(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBElectronics*)
   {
      ::RBElectronics *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBElectronics >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBElectronics", ::RBElectronics::Class_Version(), "RBElectronics.h", 17,
                  typeid(::RBElectronics), DefineBehavior(ptr, ptr),
                  &::RBElectronics::Dictionary, isa_proxy, 4,
                  sizeof(::RBElectronics) );
      instance.SetDelete(&delete_RBElectronics);
      instance.SetDeleteArray(&deleteArray_RBElectronics);
      instance.SetDestructor(&destruct_RBElectronics);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBElectronics*)
   {
      return GenerateInitInstanceLocal((::RBElectronics*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBElectronics*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_RBSisTimestampUnpacker(void *p);
   static void deleteArray_RBSisTimestampUnpacker(void *p);
   static void destruct_RBSisTimestampUnpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RBSisTimestampUnpacker*)
   {
      ::RBSisTimestampUnpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBSisTimestampUnpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBSisTimestampUnpacker", ::RBSisTimestampUnpacker::Class_Version(), "RBSisTimestampUnpacker.h", 27,
                  typeid(::RBSisTimestampUnpacker), DefineBehavior(ptr, ptr),
                  &::RBSisTimestampUnpacker::Dictionary, isa_proxy, 4,
                  sizeof(::RBSisTimestampUnpacker) );
      instance.SetDelete(&delete_RBSisTimestampUnpacker);
      instance.SetDeleteArray(&deleteArray_RBSisTimestampUnpacker);
      instance.SetDestructor(&destruct_RBSisTimestampUnpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RBSisTimestampUnpacker*)
   {
      return GenerateInitInstanceLocal((::RBSisTimestampUnpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBSisTimestampUnpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RBTimestamp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBTimestamp::Class_Name()
{
   return "RBTimestamp";
}

//______________________________________________________________________________
const char *RBTimestamp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBTimestamp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBTimestamp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBTimestamp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBTimestamp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBTimestamp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBTimestamp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBTimestamp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBHINPUnpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBHINPUnpacker::Class_Name()
{
   return "RBHINPUnpacker";
}

//______________________________________________________________________________
const char *RBHINPUnpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBHINPUnpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBHINPUnpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBHINPUnpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBHINPUnpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBHINPUnpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBHINPUnpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBHINPUnpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBHINPHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBHINPHit::Class_Name()
{
   return "RBHINPHit";
}

//______________________________________________________________________________
const char *RBHINPHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBHINPHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBHINPHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBHINPHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBHINPHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBHINPHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBHINPHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBHINPHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBCAEN7xxUnpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBCAEN7xxUnpacker::Class_Name()
{
   return "RBCAEN7xxUnpacker";
}

//______________________________________________________________________________
const char *RBCAEN7xxUnpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN7xxUnpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBCAEN7xxUnpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN7xxUnpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBCAEN7xxUnpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN7xxUnpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBCAEN7xxUnpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN7xxUnpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBCAEN1x90Unpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBCAEN1x90Unpacker::Class_Name()
{
   return "RBCAEN1x90Unpacker";
}

//______________________________________________________________________________
const char *RBCAEN1x90Unpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN1x90Unpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBCAEN1x90Unpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN1x90Unpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBCAEN1x90Unpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN1x90Unpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBCAEN1x90Unpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBCAEN1x90Unpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBPh7xxUnpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBPh7xxUnpacker::Class_Name()
{
   return "RBPh7xxUnpacker";
}

//______________________________________________________________________________
const char *RBPh7xxUnpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBPh7xxUnpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBPh7xxUnpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBPh7xxUnpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBPh7xxUnpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBPh7xxUnpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBPh7xxUnpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBPh7xxUnpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBUSBStack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBUSBStack::Class_Name()
{
   return "RBUSBStack";
}

//______________________________________________________________________________
const char *RBUSBStack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBUSBStack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBUSBStack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBUSBStack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBUSBStackMarker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBUSBStackMarker::Class_Name()
{
   return "RBUSBStackMarker";
}

//______________________________________________________________________________
const char *RBUSBStackMarker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStackMarker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBUSBStackMarker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStackMarker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBUSBStackMarker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStackMarker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBUSBStackMarker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBUSBStackMarker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBElectronics::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBElectronics::Class_Name()
{
   return "RBElectronics";
}

//______________________________________________________________________________
const char *RBElectronics::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBElectronics*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBElectronics::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBElectronics*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBElectronics::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBElectronics*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBElectronics::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBElectronics*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RBSisTimestampUnpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RBSisTimestampUnpacker::Class_Name()
{
   return "RBSisTimestampUnpacker";
}

//______________________________________________________________________________
const char *RBSisTimestampUnpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBSisTimestampUnpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBSisTimestampUnpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RBSisTimestampUnpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RBSisTimestampUnpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBSisTimestampUnpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RBSisTimestampUnpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RBSisTimestampUnpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RBTimestamp::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBTimestamp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBTimestamp::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBTimestamp::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RBTimestamp(void *p) {
      delete ((::RBTimestamp*)p);
   }
   static void deleteArray_RBTimestamp(void *p) {
      delete [] ((::RBTimestamp*)p);
   }
   static void destruct_RBTimestamp(void *p) {
      typedef ::RBTimestamp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBTimestamp

//______________________________________________________________________________
void RBHINPUnpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBHINPUnpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBHINPUnpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBHINPUnpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RBHINPUnpacker(void *p) {
      delete ((::RBHINPUnpacker*)p);
   }
   static void deleteArray_RBHINPUnpacker(void *p) {
      delete [] ((::RBHINPUnpacker*)p);
   }
   static void destruct_RBHINPUnpacker(void *p) {
      typedef ::RBHINPUnpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBHINPUnpacker

//______________________________________________________________________________
void RBHINPHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBHINPHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBHINPHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBHINPHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBHINPHit(void *p) {
      return  p ? new(p) ::RBHINPHit : new ::RBHINPHit;
   }
   static void *newArray_RBHINPHit(Long_t nElements, void *p) {
      return p ? new(p) ::RBHINPHit[nElements] : new ::RBHINPHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBHINPHit(void *p) {
      delete ((::RBHINPHit*)p);
   }
   static void deleteArray_RBHINPHit(void *p) {
      delete [] ((::RBHINPHit*)p);
   }
   static void destruct_RBHINPHit(void *p) {
      typedef ::RBHINPHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBHINPHit

//______________________________________________________________________________
void RBCAEN7xxUnpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBCAEN7xxUnpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBCAEN7xxUnpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBCAEN7xxUnpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBCAEN7xxUnpacker(void *p) {
      return  p ? new(p) ::RBCAEN7xxUnpacker : new ::RBCAEN7xxUnpacker;
   }
   static void *newArray_RBCAEN7xxUnpacker(Long_t nElements, void *p) {
      return p ? new(p) ::RBCAEN7xxUnpacker[nElements] : new ::RBCAEN7xxUnpacker[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBCAEN7xxUnpacker(void *p) {
      delete ((::RBCAEN7xxUnpacker*)p);
   }
   static void deleteArray_RBCAEN7xxUnpacker(void *p) {
      delete [] ((::RBCAEN7xxUnpacker*)p);
   }
   static void destruct_RBCAEN7xxUnpacker(void *p) {
      typedef ::RBCAEN7xxUnpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBCAEN7xxUnpacker

//______________________________________________________________________________
void RBCAEN1x90Unpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBCAEN1x90Unpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBCAEN1x90Unpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBCAEN1x90Unpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBCAEN1x90Unpacker(void *p) {
      return  p ? new(p) ::RBCAEN1x90Unpacker : new ::RBCAEN1x90Unpacker;
   }
   static void *newArray_RBCAEN1x90Unpacker(Long_t nElements, void *p) {
      return p ? new(p) ::RBCAEN1x90Unpacker[nElements] : new ::RBCAEN1x90Unpacker[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBCAEN1x90Unpacker(void *p) {
      delete ((::RBCAEN1x90Unpacker*)p);
   }
   static void deleteArray_RBCAEN1x90Unpacker(void *p) {
      delete [] ((::RBCAEN1x90Unpacker*)p);
   }
   static void destruct_RBCAEN1x90Unpacker(void *p) {
      typedef ::RBCAEN1x90Unpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBCAEN1x90Unpacker

//______________________________________________________________________________
void RBPh7xxUnpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBPh7xxUnpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBPh7xxUnpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBPh7xxUnpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBPh7xxUnpacker(void *p) {
      return  p ? new(p) ::RBPh7xxUnpacker : new ::RBPh7xxUnpacker;
   }
   static void *newArray_RBPh7xxUnpacker(Long_t nElements, void *p) {
      return p ? new(p) ::RBPh7xxUnpacker[nElements] : new ::RBPh7xxUnpacker[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBPh7xxUnpacker(void *p) {
      delete ((::RBPh7xxUnpacker*)p);
   }
   static void deleteArray_RBPh7xxUnpacker(void *p) {
      delete [] ((::RBPh7xxUnpacker*)p);
   }
   static void destruct_RBPh7xxUnpacker(void *p) {
      typedef ::RBPh7xxUnpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBPh7xxUnpacker

//______________________________________________________________________________
void RBUSBStack::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBUSBStack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBUSBStack::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBUSBStack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RBUSBStack(void *p) {
      return  p ? new(p) ::RBUSBStack : new ::RBUSBStack;
   }
   static void *newArray_RBUSBStack(Long_t nElements, void *p) {
      return p ? new(p) ::RBUSBStack[nElements] : new ::RBUSBStack[nElements];
   }
   // Wrapper around operator delete
   static void delete_RBUSBStack(void *p) {
      delete ((::RBUSBStack*)p);
   }
   static void deleteArray_RBUSBStack(void *p) {
      delete [] ((::RBUSBStack*)p);
   }
   static void destruct_RBUSBStack(void *p) {
      typedef ::RBUSBStack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBUSBStack

//______________________________________________________________________________
void RBUSBStackMarker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBUSBStackMarker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBUSBStackMarker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBUSBStackMarker::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RBUSBStackMarker(void *p) {
      delete ((::RBUSBStackMarker*)p);
   }
   static void deleteArray_RBUSBStackMarker(void *p) {
      delete [] ((::RBUSBStackMarker*)p);
   }
   static void destruct_RBUSBStackMarker(void *p) {
      typedef ::RBUSBStackMarker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBUSBStackMarker

//______________________________________________________________________________
void RBElectronics::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBElectronics.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBElectronics::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBElectronics::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RBElectronics(void *p) {
      delete ((::RBElectronics*)p);
   }
   static void deleteArray_RBElectronics(void *p) {
      delete [] ((::RBElectronics*)p);
   }
   static void destruct_RBElectronics(void *p) {
      typedef ::RBElectronics current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBElectronics

//______________________________________________________________________________
void RBSisTimestampUnpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class RBSisTimestampUnpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RBSisTimestampUnpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(RBSisTimestampUnpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RBSisTimestampUnpacker(void *p) {
      delete ((::RBSisTimestampUnpacker*)p);
   }
   static void deleteArray_RBSisTimestampUnpacker(void *p) {
      delete [] ((::RBSisTimestampUnpacker*)p);
   }
   static void destruct_RBSisTimestampUnpacker(void *p) {
      typedef ::RBSisTimestampUnpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RBSisTimestampUnpacker

namespace {
  void TriggerDictionaryInitialization_RBElectronicsDict_Impl() {
    static const char* headers[] = {
"RBElectronics.h",
"RBSisTimestampUnpacker.h",
"RBHINPUnpacker.h",
"RBCCUSBPacket.h",
"RBPh7xxUnpacker.h",
"RBCAEN7xxUnpacker.h",
"RBUSBStackMarker.h",
"RBTimestamp.h",
"RBUSBStack.h",
"RBHINPHit.h",
"RBModuleUnpacker.h",
"RBCAEN1x90Unpacker.h",
0
    };
    static const char* includePaths[] = {
"/projects/hira/Daniele/HiRAEVT/",
"/projects/hira/Daniele/HiRAEVT/electronics",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/Daniele/HiRAEVT/electronics/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$RBTimestamp.h")))  RBTimestamp;
class __attribute__((annotate("$clingAutoload$RBHINPUnpacker.h")))  RBHINPUnpacker;
class __attribute__((annotate("$clingAutoload$RBHINPUnpacker.h")))  RBHINPHit;
class __attribute__((annotate("$clingAutoload$RBCAEN7xxUnpacker.h")))  RBCAEN7xxUnpacker;
class __attribute__((annotate("$clingAutoload$RBCAEN1x90Unpacker.h")))  RBCAEN1x90Unpacker;
class __attribute__((annotate("$clingAutoload$RBPh7xxUnpacker.h")))  RBPh7xxUnpacker;
class __attribute__((annotate("$clingAutoload$RBUSBStack.h")))  RBUSBStack;
class __attribute__((annotate("$clingAutoload$RBUSBStackMarker.h")))  RBUSBStackMarker;
class __attribute__((annotate("$clingAutoload$RBElectronics.h")))  RBElectronics;
class __attribute__((annotate("$clingAutoload$RBSisTimestampUnpacker.h")))  RBSisTimestampUnpacker;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RBElectronics.h"
#include "RBSisTimestampUnpacker.h"
#include "RBHINPUnpacker.h"
#include "RBCCUSBPacket.h"
#include "RBPh7xxUnpacker.h"
#include "RBCAEN7xxUnpacker.h"
#include "RBUSBStackMarker.h"
#include "RBTimestamp.h"
#include "RBUSBStack.h"
#include "RBHINPHit.h"
#include "RBModuleUnpacker.h"
#include "RBCAEN1x90Unpacker.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RBCAEN1x90Unpacker", payloadCode, "@",
"RBCAEN7xxUnpacker", payloadCode, "@",
"RBElectronics", payloadCode, "@",
"RBHINPHit", payloadCode, "@",
"RBHINPUnpacker", payloadCode, "@",
"RBPh7xxUnpacker", payloadCode, "@",
"RBSisTimestampUnpacker", payloadCode, "@",
"RBTimestamp", payloadCode, "@",
"RBUSBStack", payloadCode, "@",
"RBUSBStackMarker", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RBElectronicsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RBElectronicsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RBElectronicsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RBElectronicsDict() {
  TriggerDictionaryInitialization_RBElectronicsDict_Impl();
}
