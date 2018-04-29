CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/HTRawDataReader
INCLUDES  += -I$(HiRAEVTSRC)/HTMapper
INCLUDES  += -I$(HiRAEVTSRC)/HTExperimentalSetup
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/HTRunInfo
INCLUDES  += -I$(HiRAEVTSRC)/electronics
INCLUDES  += -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTSisTimestampe15190
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTHiRA
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTNeutronWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTVetoWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTForwardArray
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTMicroball

RLIBS     := -L$(HiRAEVTLIB) -lHTRunInfo -lHTDetector -lHTRootElectronics

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

HTRAWDATAREADER_LIB := libHTRawDataReader.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTRAWDATAREADER_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(HTRAWDATAREADER_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(HTRAWDATAREADER_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTRAWDATAREADER_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTRAWDATAREADER_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
