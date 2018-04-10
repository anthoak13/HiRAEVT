//
// File generated by rootcint at Tue Apr 10 19:31:11 2018

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME RBSetupDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "RBSetupDict.h"

#include "TClass.h"
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

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOTShadow {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOTShadow
// END OF SHADOWS

namespace ROOTDict {
   void RBSetup_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_RBSetup(void *p = 0);
   static void *newArray_RBSetup(Long_t size, void *p);
   static void delete_RBSetup(void *p);
   static void deleteArray_RBSetup(void *p);
   static void destruct_RBSetup(void *p);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::RBSetup*)
   {
      ::RBSetup *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RBSetup >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RBSetup", ::RBSetup::Class_Version(), "./RBSetup.h", 11,
                  typeid(::RBSetup), ::ROOT::DefineBehavior(ptr, ptr),
                  &::RBSetup::Dictionary, isa_proxy, 4,
                  sizeof(::RBSetup) );
      instance.SetNew(&new_RBSetup);
      instance.SetNewArray(&newArray_RBSetup);
      instance.SetDelete(&delete_RBSetup);
      instance.SetDeleteArray(&deleteArray_RBSetup);
      instance.SetDestructor(&destruct_RBSetup);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::RBSetup*)
   {
      return GenerateInitInstanceLocal((::RBSetup*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RBSetup*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOTDict

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
   return ::ROOTDict::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RBSetup::ImplFileLine()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void RBSetup::Dictionary()
{
   fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *RBSetup::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gCINTMutex); if(!fgIsA) {fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::RBSetup*)0x0)->GetClass();} }
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

//______________________________________________________________________________
void RBSetup::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class RBSetup.
      TClass *R__cl = ::RBSetup::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*fExperiment", &fExperiment);
      TNamed::ShowMembers(R__insp);
}

namespace ROOTDict {
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
} // end of namespace ROOTDict for class ::RBSetup

/********************************************************
* RBSetupDict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableRBSetupDict();

extern "C" void G__set_cpp_environmentRBSetupDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("RBSetup.h");
  G__cpp_reset_tagtableRBSetupDict();
}
#include <new>
extern "C" int G__cpp_dllrevRBSetupDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* RBSetup */
static int G__RBSetupDict_555_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   RBSetup* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new RBSetup[n];
     } else {
       p = new((void*) gvp) RBSetup[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new RBSetup;
     } else {
       p = new((void*) gvp) RBSetup;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((RBSetup*) G__getstructoffset())->GetInitializedExp());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((RBSetup*) G__getstructoffset())->Print();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) RBSetup::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) RBSetup::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) RBSetup::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      RBSetup::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((RBSetup*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) RBSetup::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) RBSetup::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) RBSetup::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__RBSetupDict_555_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) RBSetup::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__RBSetupDict_555_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   RBSetup* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new RBSetup(*(RBSetup*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef RBSetup G__TRBSetup;
static int G__RBSetupDict_555_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (RBSetup*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((RBSetup*) (soff+(sizeof(RBSetup)*i)))->~G__TRBSetup();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (RBSetup*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((RBSetup*) (soff))->~G__TRBSetup();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__RBSetupDict_555_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   RBSetup* dest = (RBSetup*) G__getstructoffset();
   *dest = *(RBSetup*) libp->para[0].ref;
   const RBSetup& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* RBSetup */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncRBSetupDict {
 public:
  G__Sizep2memfuncRBSetupDict(): p(&G__Sizep2memfuncRBSetupDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncRBSetupDict::*p)();
};

size_t G__get_sizep2memfuncRBSetupDict()
{
  G__Sizep2memfuncRBSetupDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceRBSetupDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup))) {
     RBSetup *G__Lderived;
     G__Lderived=(RBSetup*)0x1000;
     {
       TNamed *G__Lpbase=(TNamed*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup),G__get_linked_tagnum(&G__RBSetupDictLN_TNamed),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup),G__get_linked_tagnum(&G__RBSetupDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableRBSetupDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__RBSetupDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__RBSetupDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__RBSetupDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__RBSetupDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<std::string,TObjArray*>",117,G__get_linked_tagnum(&G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*>",117,G__get_linked_tagnum(&G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("map<string,TObjArray*,less<string> >",117,G__get_linked_tagnum(&G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<UShort_t>",117,G__get_linked_tagnum(&G__RBSetupDictLN_vectorlEunsignedsPshortcOallocatorlEunsignedsPshortgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__RBSetupDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__RBSetupDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__RBSetupDictLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__RBSetupDictLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* RBSetup */
static void G__setup_memvarRBSetup(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup));
   { RBSetup *p; p=(RBSetup*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__RBSetupDictLN_RBExperiment),-1,-1,4,"fExperiment=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__RBSetupDictLN_TClass),G__defined_typename("atomic_TClass_ptr"),-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarRBSetupDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncRBSetup(void) {
   /* RBSetup */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup));
   G__memfunc_setup("RBSetup",677,G__RBSetupDict_555_0_1, 105, G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetInitializedExp",1731,G__RBSetupDict_555_0_2, 85, G__get_linked_tagnum(&G__RBSetupDictLN_RBExperiment), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Print",525,G__RBSetupDict_555_0_3, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__RBSetupDict_555_0_4, 85, G__get_linked_tagnum(&G__RBSetupDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&RBSetup::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__RBSetupDict_555_0_5, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&RBSetup::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__RBSetupDict_555_0_6, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&RBSetup::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__RBSetupDict_555_0_7, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&RBSetup::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__RBSetupDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__RBSetupDict_555_0_11, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__RBSetupDict_555_0_12, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&RBSetup::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__RBSetupDict_555_0_13, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&RBSetup::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__RBSetupDict_555_0_14, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&RBSetup::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__RBSetupDict_555_0_15, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&RBSetup::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("RBSetup", 677, G__RBSetupDict_555_0_16, (int) ('i'), G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup), -1, 0, 1, 1, 1, 0, "u 'RBSetup' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~RBSetup", 803, G__RBSetupDict_555_0_17, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__RBSetupDict_555_0_18, (int) ('u'), G__get_linked_tagnum(&G__RBSetupDictLN_RBSetup), -1, 1, 1, 1, 1, 0, "u 'RBSetup' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncRBSetupDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {
}

static void G__cpp_setup_global3() {
}

static void G__cpp_setup_global4() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalRBSetupDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
  G__cpp_setup_global3();
  G__cpp_setup_global4();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {
}

static void G__cpp_setup_func20() {
}

static void G__cpp_setup_func21() {
}

static void G__cpp_setup_func22() {
}

static void G__cpp_setup_func23() {
}

static void G__cpp_setup_func24() {
}

static void G__cpp_setup_func25() {
}

static void G__cpp_setup_func26() {
}

static void G__cpp_setup_func27() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcRBSetupDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
  G__cpp_setup_func20();
  G__cpp_setup_func21();
  G__cpp_setup_func22();
  G__cpp_setup_func23();
  G__cpp_setup_func24();
  G__cpp_setup_func25();
  G__cpp_setup_func26();
  G__cpp_setup_func27();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__RBSetupDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TNamed = { "TNamed" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_vectorlEunsignedsPshortcOallocatorlEunsignedsPshortgRsPgR = { "vector<unsigned short,allocator<unsigned short> >" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR = { "map<string,TObjArray*,less<string>,allocator<pair<const string,TObjArray*> > >" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_RBExperiment = { "RBExperiment" , 99 , -1 };
G__linked_taginfo G__RBSetupDictLN_RBSetup = { "RBSetup" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableRBSetupDict() {
  G__RBSetupDictLN_TClass.tagnum = -1 ;
  G__RBSetupDictLN_TBuffer.tagnum = -1 ;
  G__RBSetupDictLN_TMemberInspector.tagnum = -1 ;
  G__RBSetupDictLN_TObject.tagnum = -1 ;
  G__RBSetupDictLN_TNamed.tagnum = -1 ;
  G__RBSetupDictLN_vectorlEunsignedsPshortcOallocatorlEunsignedsPshortgRsPgR.tagnum = -1 ;
  G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__RBSetupDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__RBSetupDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR.tagnum = -1 ;
  G__RBSetupDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__RBSetupDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__RBSetupDictLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__RBSetupDictLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__RBSetupDictLN_RBExperiment.tagnum = -1 ;
  G__RBSetupDictLN_RBSetup.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableRBSetupDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TNamed);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_vectorlEunsignedsPshortcOallocatorlEunsignedsPshortgRsPgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__RBSetupDictLN_RBExperiment);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__RBSetupDictLN_RBSetup),sizeof(RBSetup),-1,324864,(char*)NULL,G__setup_memvarRBSetup,G__setup_memfuncRBSetup);
}
extern "C" void G__cpp_setupRBSetupDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupRBSetupDict()");
  G__set_cpp_environmentRBSetupDict();
  G__cpp_setup_tagtableRBSetupDict();

  G__cpp_setup_inheritanceRBSetupDict();

  G__cpp_setup_typetableRBSetupDict();

  G__cpp_setup_memvarRBSetupDict();

  G__cpp_setup_memfuncRBSetupDict();
  G__cpp_setup_globalRBSetupDict();
  G__cpp_setup_funcRBSetupDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncRBSetupDict();
  return;
}
class G__cpp_setup_initRBSetupDict {
  public:
    G__cpp_setup_initRBSetupDict() { G__add_setup_func("RBSetupDict",(G__incsetup)(&G__cpp_setupRBSetupDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initRBSetupDict() { G__remove_setup_func("RBSetupDict"); }
};
G__cpp_setup_initRBSetupDict G__cpp_setup_initializerRBSetupDict;

