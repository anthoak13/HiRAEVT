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


RBEXPERIMENT_DICT        := RBExperimentDict.$(SrcSuf)
RBEXPERIMENT_DICTH       := $(RBEXPERIMENT_DICT:.$(SrcSuf)=.h)
RBEXPERIMENT_DICTO       := $(RBEXPERIMENT_DICT:.$(SrcSuf)=.$(ObjSuf))

RBEXPERIMENT_SRCS        := RBExperiment.$(SrcSuf) RBRingItem.$(SrcSuf) RBRingStateChangeItem.$(SrcSuf) RBNSCLBufferHeader.$(SrcSuf)

RBEXPERIMENT_HDRS        := $(RBEXPERIMENT_SRCS:.$(SrcSuf)=.h) RBExperimentLinkDef.h
RBEXPERIMENT_HDRS        := $(filter-out $(RBEXPERIMENT_DICTH),$(RBEXPERIMENT_HDRS))

RBEXPERIMENT_LIB         := libRBExperiment.$(DllSuf)

RBEXPERIMENT_OBJS        := $(RBEXPERIMENT_SRCS:.$(SrcSuf)=.$(ObjSuf))

RLIBS             := -L$(RIBbitLIB)

INCLUDES += -I../
INCLUDES += -I../electronics
INCLUDES += -I../utilities/RBNucleus
INCLUDES += -I../utilities/RBAme
INCLUDES += -I../detectors/RBDetector
INCLUDES += -I../detectors/RBA1900
INCLUDES += -I../detectors/RBHiRA
INCLUDES += -I../detectors/RBMcp

CXXFLAGS += -g $(INCLUDES)


############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -Wno-unused-variable -Wno-unused-value -Wno-unused-parameter -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) $(ExeSuf) .$(DllSuf)

all:  $(RBEXPERIMENT_LIB)

$(RBEXPERIMENT_DICT): $(RBEXPERIMENT_HDRS)
	@echo "Generating dictionary $@... $(RBEXPERIMENT_DICT) $(SrcSuf)"
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(RBEXPERIMENT_LIB): $(RBEXPERIMENT_OBJS) $(RBEXPERIMENT_DICTO)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(INCLUDES) $(LDFLAGS) $^ $(OutPutOpt) $@ $(GLIBS) $(RLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(RLIBS) $(OutPutOpt)$@
endif

RBEXPERIMENT:    $(RBEXPERIMENT_LIB)

install:
	@cp $(RBEXPERIMENT_LIB) $(RIBbitLIB)/.

distclean: clean
	@rm -f $(RBEXPERIMENT_LIB) $(RBEXPERIMENT_DICT) $(RBEXPERIMENT_DICTH)
	@rm -f $(RIBbitLIB)/$(RBEXPERIMENT_LIB) 

clean:
	@rm -f $(RBEXPERIMENT_OBJS) $(RBEXPERIMENT_DICTO) $(RBEXPERIMENT_DICT) $(RBEXPERIMENT_DICTH) $(RBEXPERIMENT_LIB)

