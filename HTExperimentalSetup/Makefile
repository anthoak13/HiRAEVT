CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/HTExperimentalSetup
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/HTRunInfo
INCLUDES  += -I$(HiRAEVTSRC)/electronics


#Add all of the directories in the detector folder
DETSUBDIR := $(sort $(dir $(wildcard ${HiRAEVTSRC}/detectors/*/)))
INCLUDES += $(patsubst %, -I%, ${DETSUBDIR})

DETLIBS := $(filter-out ${HiRAEVTSTC}/%, $(patsubst ${HiRAEVTSRC}/detectors/%/, -l%, ${DETSUBDIR}))


RLIBS     := -L$(HiRAEVTLIB) -lHTRunInfo
RLIBS += ${DETLIBS}

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

HTEXPERIMENTALSETUP_LIB := libHTExperimentalSetup.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTEXPERIMENTALSETUP_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(HTEXPERIMENTALSETUP_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(HTEXPERIMENTALSETUP_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTEXPERIMENTALSETUP_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTEXPERIMENTALSETUP_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
