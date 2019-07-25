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

RLIBS     := -L$(HiRAEVTLIB) -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

DETECTOR_LIB := lib${DETECTOR_NAME}.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

%.$(ObjSuf): %.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(DETECTOR_LIB)


$(DETECTOR_LIB): $(OBJS)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(DETECTOR_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(DETECTOR_LIB)
	@rm -f $(HiRAEVTLIB)/$(DETECTOR_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
