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

RIBBITLOGO_SRCS        := RIBbit2Logo.$(SrcSuf)

RIBBITLOGO_HDRS        := $(RIBBITLOGO_SRCS:.$(SrcSuf)=.h)

RIBBITLOGO_OBJS        := $(RIBBITLOGO_SRCS:.$(SrcSuf)=.$(ObjSuf))

RIBBITLOGO_LIB         := libRIBbitLogo.$(DllSuf)

INCLUDES += -I$(RIBbitSRC)

CXXFLAGS += $(INCLUDES) -g


############# RULES ###############

.$(SrcSuf).$(ObjSuf):
	$(CXX) -g $(CXXFLAGS) -Wno-unused-variable -Wno-unused-value -Wno-unused-parameter -c $<

############# TARGETS #############

.SUFFIXES: .$(SrcSuf) .$(ObjSuf)

all:  $(RIBBITLOGO_LIB)

$(RIBBITLOGO_DICT): $(RIBBITLOGO_HDRS)
	@echo "Generating dictionary $@... $(RIBBITLOGO_DICT) $(SrcSuf)"
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(RIBBITLOGO_LIB): $(RIBBITLOGO_OBJS)
ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS)$@ $(INCLUDES) $(LDFLAGS) $^ $(OutPutOpt) $@ $(GLIBS) $(RLIBS)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(GLIBS) $(RLIBS) $(OutPutOpt)$@
endif

install:
	@cp $(RIBBITLOGO_LIB) $(RIBbitLIB)/.

distclean: clean

clean:
	@rm -f $(RIBBITLOGO_OBJS)
