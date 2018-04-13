############# MACROS ##############

RC     := root-config
ifeq ($(shell which $(RC) 2>&1 | sed -ne "s@.*/$(RC)@$(RC)@p"),$(RC))
MKARCH := $(wildcard $(shell $(RC) --etcdir)/Makefile.arch)
endif
ifneq ($(MKARCH),)
include $(MKARCH)
else
ROOTSYS = ..
include $(ROOTSYS)/etc/Makefile.arch
endif


RBSETUP_DICT        := RBSetupDict.$(SrcSuf)
RBSETUP_DICTH       := $(RBSETUP_DICT:.$(SrcSuf)=.h)
RBSETUP_DICTO       := $(RBSETUP_DICT:.$(SrcSuf)=.$(ObjSuf))

RBSETUP_SRCS        := RBSetup.$(SrcSuf)

RBSETUP_HDRS        := $(RBSETUP_SRCS:.$(SrcSuf)=.h) RBSetupLinkDef.h
RBSETUP_HDRS        := $(filter-out $(RBSETUP_DICTH),$(RBSETUP_HDRS))

RBSETUP_LIB         := libRBSetup.$(DllSuf).1.0

RBSETUP_OBJS        := $(RBSETUP_SRCS:.$(SrcSuf)=.$(ObjSuf))

RLIBS             := -L$(RIBbitLIB) -lRBElectronics -lRBExperiment -lRBShared

INCLUDES += -I$(RIBbitSRC)
INCLUDES += -I$(RIBbitSRC)/settings
INCLUDES += -I$(RIBbitSRC)/electronics
INCLUDES += -I$(RIBbitSRC)/RBExperiment
INCLUDES += -I$(RIBbitSRC)/shared

CXXFLAGS += $(INCLUDES) -g


############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) -g $(CXXFLAGS) -Wno-unused-variable -Wno-unused-value -Wno-unused-parameter -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) $(ExeSuf) .$(DllSuf)

all:  $(RBSETUP_LIB)

$(RBSETUP_DICT): $(RBSETUP_HDRS)
	@echo "Generating dictionary $@... $(RBSETUP_DICT) $(SrcSuf)"
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(RBSETUP_LIB): $(RBSETUP_OBJS) $(RBSETUP_DICTO)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(INCLUDES) $(LDFLAGS) $^ $(OutPutOpt) $@ $(GLIBS) $(RLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(RLIBS) $(OutPutOpt)$@
endif

RBSETUP:    $(RBSETUP_LIB)

install:
	@cp $(RBSETUP_LIB) $(RIBbitLIB)/.

distclean: clean
	@rm -f $(RBSETUP_LIB) $(RBSETUP_DICT) $(RBSETUP_DICTH)
	@rm -f $(RIBbitLIB)/$(RBSETUP_LIB)

clean:
	@rm -f $(RBSETUP_OBJS) $(RBSETUP_DICTO) $(RBSETUP_DICT) $(RBSETUP_DICTH) $(RBSETUP_LIB)
