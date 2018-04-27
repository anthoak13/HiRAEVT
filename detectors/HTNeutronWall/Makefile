CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTNeutronWall

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

HTNEUTRONWALL_DICT  := HTNeutronWallDict.$(SrcSuf)
HTNEUTRONWALL_DICTH := $(HTNEUTRONWALL_DICT:.$(SrcSuf)=.h)
HTNEUTRONWALL_DICTO := $(HTNEUTRONWALL_DICT:.$(SrcSuf)=.$(ObjSuf))
HTNEUTRONWALL_PCM   := HTNeutronWallDict$(PcmSuf)

HTNEUTRONWALL_HDRS  := $(wildcard HT*.$(SrcSuf))

HTNEUTRONWALL_HDRS  := $(HTNEUTRONWALL_HDRS:.$(SrcSuf)=.h) HTNeutronWallLinkDef.h
HTNEUTRONWALL_HDRS  := $(filter-out $(HTNEUTRONWALL_DICTH),$(HTNEUTRONWALL_HDRS))

HTNEUTRONWALL_LIB := libHTNeutronWall.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTNEUTRONWALL_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(HTNEUTRONWALL_DICT): $(HTNEUTRONWALL_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(HTNEUTRONWALL_LIB): $(OBJS) $(HTNEUTRONWALL_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(HTNEUTRONWALL_LIB) $(HTNEUTRONWALL_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTNEUTRONWALL_LIB) $(HTNEUTRONWALL_DICT) $(HTNEUTRONWALL_DICTH) $(HTNEUTRONWALL_PCM)
	@rm -f $(HiRAEVTLIB)/$(HTNEUTRONWALL_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(HTNEUTRONWALL_DICTO) $(HTNEUTRONWALL_DICT) $(HTNEUTRONWALL_DICTH) $(HTNEUTRONWALL_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
