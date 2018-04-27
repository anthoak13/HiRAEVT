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
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTMicroball

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

HTMICROBALL_DICT  := HTMicroballDict.$(SrcSuf)
HTMICROBALL_DICTH := $(HTMICROBALL_DICT:.$(SrcSuf)=.h)
HTMICROBALL_DICTO := $(HTMICROBALL_DICT:.$(SrcSuf)=.$(ObjSuf))
HTMICROBALL_PCM   := HTMicroballDict$(PcmSuf)

HTMICROBALL_HDRS  := $(wildcard HT*.$(SrcSuf))

HTMICROBALL_HDRS  := $(HTMICROBALL_HDRS:.$(SrcSuf)=.h) HTMicroballLinkDef.h
HTMICROBALL_HDRS  := $(filter-out $(HTMICROBALL_DICTH),$(HTMICROBALL_HDRS))

HTMICROBALL_LIB := libHTMicroball.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTMICROBALL_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(HTMICROBALL_DICT): $(HTMICROBALL_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(HTMICROBALL_LIB): $(OBJS) $(HTMICROBALL_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(HTMICROBALL_LIB) $(HTMICROBALL_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTMICROBALL_LIB) $(HTMICROBALL_DICT) $(HTMICROBALL_DICTH) $(HTMICROBALL_PCM)
	@rm -f $(HiRAEVTLIB)/$(HTMICROBALL_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(HTMICROBALL_DICTO) $(HTMICROBALL_DICT) $(HTMICROBALL_DICTH) $(HTMICROBALL_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
