############# MACROS ##############
RC     := root-config
ifeq ($(shell which $(RC) 2>&1 | sed -ne "s@.*/$(RC)@$(RC)@p"),$(RC))
MKARCH := $(wildcard $(shell $(RC) --etcdir)/Makefile.arch)
endif
ifneq ($(MKARCH),)
include $(MKARCH)
else
ROOTSYS = ../
include $(ROOTSYS)/etc/Makefile.arch
endif

RBELECTRONICS_DICT        := RBElectronicsDict.$(SrcSuf)
RBELECTRONICS_DICTH       := $(RBELECTRONICS_DICT:.$(SrcSuf)=.h)
RBELECTRONICS_DICTO       := $(RBELECTRONICS_DICT:.$(SrcSuf)=.$(ObjSuf))

RBELECTRONICS_SRCS        := $(wildcard RB*.$(SrcSuf))

RBELECTRONICS_HDRS        := $(RBELECTRONICS_SRCS:.$(SrcSuf)=.h) RBElectronicsLinkDef.h
RBELECTRONICS_HDRS        := $(filter-out $(RBELECTRONICS_DICTH),$(RBELECTRONICS_HDRS))

RBELECTRONICS_LIB         := libRBElectronics.$(DllSuf)

RBELECTRONICS_OBJS        := $(RBELECTRONICS_SRCS:.$(SrcSuf)=.$(ObjSuf))

RLIBS             := -L$(RIBbitLIB)

INCLUDES += -I../..

CXXFLAGS += -g $(INCLUDES)


############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -Wno-unused-variable -Wno-unused-value -Wno-unused-parameter -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) $(ExeSuf) .$(DllSuf)

all:  $(RBELECTRONICS_LIB)

$(RBELECTRONICS_DICT): $(RBELECTRONICS_HDRS)
	@echo "Generating dictionary $@... $(RBELECTRONICS_DICT) $(SrcSuf)"
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(RBELECTRONICS_LIB): $(RBELECTRONICS_OBJS) $(RBELECTRONICS_DICTO)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(INCLUDES) $(LDFLAGS) $^ $(OutPutOpt) $@ $(GLIBS) $(RLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(RLIBS) $(OutPutOpt)$@
endif

RBELECTRONICS:    $(RBELECTRONICS_LIB)

install:
	@cp $(RBELECTRONICS_LIB) $(RIBbitLIB)/.

distclean: clean
	@rm -f $(RBELECTRONICS_LIB) $(RBELECTRONICS_DICT) $(RBELECTRONICS_DICTH)
	@rm -f $(RIBbitLIB)/$(RBELECTRONICS_LIB) $(RIBbitLIB)$(RBELECTRONICS_DICT) $(RIBbitLIB)/$(RBELECTRONICS_DICTH)

clean:
	@rm -f $(RBELECTRONICS_OBJS) $(RBELECTRONICS_DICTO) $(RBELECTRONICS_DICT) $(RBELECTRONICS_DICTH) $(RBELECTRONICS_LIB)
