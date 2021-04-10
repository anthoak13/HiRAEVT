# Set the detector name
DETECTOR_NAME := $(shell basename `pwd`)

CFLAGS    := $(shell root-config --cflags --libs)
SYSLIB    := -lz -l TreePlayer -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

#Get all of the subdirectors in the parent folder and add them to the includes
SUBDIR := $(sort $(dir $(wildcard ${CURDIR}/../*/)))
INCLUDES := $(patsubst %, -I%, ${SUBDIR})

INCLUDES  += -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/electronics
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

DETECTOR_DICT  := ${DETECTOR_NAME}Dict.$(SrcSuf)
DETECTOR_DICTH := $(DETECTOR_DICT:.$(SrcSuf)=.h)
DETECTOR_DICTO := $(DETECTOR_DICT:.$(SrcSuf)=.$(ObjSuf))
DETECTOR_PCM   := ${DETECTOR_NAME}Dict$(PcmSuf)

DETECTOR_HDRS  := $(wildcard HT*.$(SrcSuf))

DETECTOR_HDRS  := $(DETECTOR_HDRS:.$(SrcSuf)=.h) ${DETECTOR_NAME}LinkDef.h
DETECTOR_HDRS  := $(filter-out $(DETECTOR_DICTH),$(DETECTOR_HDRS))

DETECTOR_LIB := lib${DETECTOR_NAME}.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@echo "Building $<"
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)


all: $(DETECTOR_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(DETECTOR_DICT): $(DETECTOR_HDRS)
	@echo "Generating dictionary $@..."
	@$(ROOTCLINGORCINT) -f $@ -p $(INCLUDES) $^

$(DETECTOR_LIB): $(OBJS) $(DETECTOR_DICTO)
	@echo "Linking $@"
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@


install:
	@cp $(DETECTOR_LIB) $(DETECTOR_PCM) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(DETECTOR_LIB) $(DETECTOR_DICT) $(DETECTOR_DICTH) $(DETECTOR_PCM)
	@rm -f $(HiRAEVTLIB)/$(DETECTOR_LIB)
	@rm -f $(HiRAEVTLIB)/$(DETECTOR_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(DETECTOR_DICTO) $(DETECTOR_DICT) $(DETECTOR_DICTH) $(DETECTOR_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
