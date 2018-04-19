CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(RIBbitSRC)/
INCLUDES  += -I$(RIBbitSRC)/electronics
INCLUDES  += -I$(RIBbitSRC)/shared
INCLUDES  += -I$(RIBbitSRC)/RBRunInfo
INCLUDES  += -I$(RIBbitSRC)/RBSetup
INCLUDES  += -I$(RIBbitSRC)/RBExperiment
INCLUDES  += -I$(RIBbitSRC)/FilterUnpacker

RLIBS     := -L$(RIBbitLIB)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

RBSETUP_DICT  := RBSetupDict.$(SrcSuf)
RBSETUP_DICTH := $(RBSETUP_DICT:.$(SrcSuf)=.h)
RBSETUP_DICTO := $(RBSETUP_DICT:.$(SrcSuf)=.$(ObjSuf))
RBSETUP_PCM   := RBSetupDict$(PcmSuf)

RBSETUP_HDRS  := $(wildcard RB*.$(SrcSuf))

RBSETUP_HDRS  := $(RBSETUP_HDRS:.$(SrcSuf)=.h) RBSetupLinkDef.h
RBSETUP_HDRS  := $(filter-out $(RBSETUP_DICTH),$(RBSETUP_HDRS))

RBSETUP_LIB := libRBSetup.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(RBSETUP_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(RBSETUP_DICT): $(RBSETUP_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(RBSETUP_LIB): $(OBJS) $(RBSETUP_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(RBSETUP_LIB) $(RBSETUP_PCM) $(RIBbitLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(RBSETUP_LIB) $(RBSETUP_DICT) $(RBSETUP_DICTH) $(RBSETUP_PCM)
	@rm -f $(RIBbitLIB)/$(RBSETUP_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(RBSETUP_DICTO) $(RBSETUP_DICT) $(RBSETUP_DICTH) $(RBSETUP_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
