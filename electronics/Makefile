CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lz -l TreePlayer -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/electronics

RLIBS     := -L$(HiRAEVTLIB)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

RBELECTRONICS_DICT  := RBElectronicsDict.$(SrcSuf)
RBELECTRONICS_DICTH := $(RBELECTRONICS_DICT:.$(SrcSuf)=.h)
RBELECTRONICS_DICTO := $(RBELECTRONICS_DICT:.$(SrcSuf)=.$(ObjSuf))
RBELECTRONICS_PCM   := RBElectronicsDict$(PcmSuf)

RBELECTRONICS_HDRS  := $(wildcard RB*.$(SrcSuf))

RBELECTRONICS_HDRS  := $(RBELECTRONICS_HDRS:.$(SrcSuf)=.h) RBElectronicsLinkDef.h
RBELECTRONICS_HDRS  := $(filter-out $(RBELECTRONICS_DICTH),$(RBELECTRONICS_HDRS))

RBELECTRONICS_LIB := libRBElectronics.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(RBELECTRONICS_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(RBELECTRONICS_DICT): $(RBELECTRONICS_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(RBELECTRONICS_LIB): $(OBJS) $(RBELECTRONICS_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(RBELECTRONICS_LIB) $(RBELECTRONICS_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(RBELECTRONICS_LIB) $(RBELECTRONICS_DICT) $(RBELECTRONICS_DICTH) $(RBELECTRONICS_PCM)
	@rm -f $(HiRAEVTLIB)/$(RBELECTRONICS_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(RBELECTRONICS_DICTO) $(RBELECTRONICS_DICT) $(RBELECTRONICS_DICTH) $(RBELECTRONICS_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
