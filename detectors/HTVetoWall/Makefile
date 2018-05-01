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
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTVetoWall

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

HTVETOWALL_DICT  := HTVetoWallDict.$(SrcSuf)
HTVETOWALL_DICTH := $(HTVETOWALL_DICT:.$(SrcSuf)=.h)
HTVETOWALL_DICTO := $(HTVETOWALL_DICT:.$(SrcSuf)=.$(ObjSuf))
HTVETOWALL_PCM   := HTVetoWallDict$(PcmSuf)

HTVETOWALL_HDRS  := $(wildcard HT*.$(SrcSuf))

HTVETOWALL_HDRS  := $(HTVETOWALL_HDRS:.$(SrcSuf)=.h) HTVetoWallLinkDef.h
HTVETOWALL_HDRS  := $(filter-out $(HTVETOWALL_DICTH),$(HTVETOWALL_HDRS))

HTVETOWALL_LIB := libHTVetoWall.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTVETOWALL_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(HTVETOWALL_DICT): $(HTVETOWALL_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(HTVETOWALL_LIB): $(OBJS) $(HTVETOWALL_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(HTVETOWALL_LIB) $(HTVETOWALL_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTVETOWALL_LIB) $(HTVETOWALL_DICT) $(HTVETOWALL_DICTH) $(HTVETOWALL_PCM)
	@rm -f $(HiRAEVTLIB)/$(HTVETOWALL_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTVETOWALL_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(HTVETOWALL_DICTO) $(HTVETOWALL_DICT) $(HTVETOWALL_DICTH) $(HTVETOWALL_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
