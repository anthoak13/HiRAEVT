CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/electronics
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTHiRA

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

HTHIRA_DICT  := HTHiRADict.$(SrcSuf)
HTHIRA_DICTH := $(HTHIRA_DICT:.$(SrcSuf)=.h)
HTHIRA_DICTO := $(HTHIRA_DICT:.$(SrcSuf)=.$(ObjSuf))
HTHIRA_PCM   := HTHiRADict$(PcmSuf)

HTHIRA_HDRS  := $(wildcard HT*.$(SrcSuf))

HTHIRA_HDRS  := $(HTHIRA_HDRS:.$(SrcSuf)=.h) HTHiRALinkDef.h
HTHIRA_HDRS  := $(filter-out $(HTHIRA_DICTH),$(HTHIRA_HDRS))

HTHIRA_LIB := libHTHiRA.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTHIRA_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(HTHIRA_DICT): $(HTHIRA_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(HTHIRA_LIB): $(OBJS) $(HTHIRA_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(HTHIRA_LIB) $(HTHIRA_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTHIRA_LIB) $(HTHIRA_DICT) $(HTHIRA_DICTH) $(HTHIRA_PCM)
	@rm -f $(HiRAEVTLIB)/$(HTHIRA_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(HTHIRA_DICTO) $(HTHIRA_DICT) $(HTHIRA_DICTH) $(HTHIRA_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
