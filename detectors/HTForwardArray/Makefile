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
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTForwardArray

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

HTFORWARDARRAY_DICT  := HTForwardArrayDict.$(SrcSuf)
HTFORWARDARRAY_DICTH := $(HTFORWARDARRAY_DICT:.$(SrcSuf)=.h)
HTFORWARDARRAY_DICTO := $(HTFORWARDARRAY_DICT:.$(SrcSuf)=.$(ObjSuf))
HTFORWARDARRAY_PCM   := HTForwardArrayDict$(PcmSuf)

HTFORWARDARRAY_HDRS  := $(wildcard HT*.$(SrcSuf))

HTFORWARDARRAY_HDRS  := $(HTFORWARDARRAY_HDRS:.$(SrcSuf)=.h) HTForwardArrayLinkDef.h
HTFORWARDARRAY_HDRS  := $(filter-out $(HTFORWARDARRAY_DICTH),$(HTFORWARDARRAY_HDRS))

HTFORWARDARRAY_LIB := libHTForwardArray.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTFORWARDARRAY_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(HTFORWARDARRAY_DICT): $(HTFORWARDARRAY_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(HTFORWARDARRAY_LIB): $(OBJS) $(HTFORWARDARRAY_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(HTFORWARDARRAY_LIB) $(HTFORWARDARRAY_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTFORWARDARRAY_LIB) $(HTFORWARDARRAY_DICT) $(HTFORWARDARRAY_DICTH) $(HTFORWARDARRAY_PCM)
	@rm -f $(HiRAEVTLIB)/$(HTFORWARDARRAY_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTFORWARDARRAY_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(HTFORWARDARRAY_DICTO) $(HTFORWARDARRAY_DICT) $(HTFORWARDARRAY_DICTH) $(HTFORWARDARRAY_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
