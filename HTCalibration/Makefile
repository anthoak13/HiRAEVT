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
INCLUDES  += -I$(HiRAEVTSRC)/HTCalibration
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTSisTimestampe15190
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTHiRA
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTNeutronWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTVetoWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTForwardArray
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTMicroball
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTTDCSpare
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTIonChamber


RLIBS     := -L$(HiRAEVTLIB) -lHTRunInfo -lHTDetector

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

THIS_LIB := libHTCalibration.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(THIS_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(THIS_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(THIS_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(THIS_LIB)
	@rm -f $(HiRAEVTLIB)/$(THIS_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
