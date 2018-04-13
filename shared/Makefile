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

RIBBITSHARED_SRCS        := RBShared.$(SrcSuf)

RIBBITSHARED_HDRS        := $(RIBBITSHARED_SRCS:.$(SrcSuf)=.h)

RIBBITSHARED_OBJS        := $(RIBBITSHARED_SRCS:.$(SrcSuf)=.$(ObjSuf))

RIBBITSHARED_LIB         := libRBShared.$(DllSuf)

INCLUDES += -I$(RIBbitSRC)
INCLUDES += -I$(RIBbitSRC)/FilterUnpacker
INCLUDES += -I$(RIBbitSRC)/RBExperiment
INCLUDES += -I$(RIBbitSRC)/electronics

CXXFLAGS += $(INCLUDES) -g


############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) -g $(CXXFLAGS) -Wno-unused-variable -Wno-unused-value -Wno-unused-parameter -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf)

all:  $(RIBBITSHARED_LIB)

$(RIBBITSHARED_DICT): $(RIBBITSHARED_HDRS)
	@echo "Generating dictionary $@... $(RIBBITSHARED_DICT) $(SrcSuf)"
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(RIBBITSHARED_LIB): $(RIBBITSHARED_OBJS)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(INCLUDES) $(LDFLAGS) $^ $(OutPutOpt) $@ $(GLIBS) $(RLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(RLIBS) $(OutPutOpt)$@
endif

install:
	@cp $(RIBBITSHARED_LIB) $(RIBbitLIB)/.

distclean: clean

clean:
	@rm -f $(RIBBITSHARED_OBJS)
