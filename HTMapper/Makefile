CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/HTMapper
INCLUDES  += -I$(HiRAEVTSRC)/logo
INCLUDES  += -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/HTRunInfo
INCLUDES  += -I$(HiRAEVTSRC)/electronics
INCLUDES  += -I$(HiRAEVTSRC)/HTExperimentalSetup
INCLUDES  += -I$(HiRAEVTSRC)/HTRawDataReader
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTSisTimestampe15190
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTHiRA
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTNeutronWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTVetoWall
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTForwardArray
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTMicroball

RLIBS     := -L$(HiRAEVTLIB) -lHTLogo -lHTShared -lHTRunInfo -lHTExperimentalSetup -lHTRootElectronics -lHTDetector -lHTDetectorMap  -lHTRawDataReader -lHTHiRA -lHTNeutronWall -lHTVetoWall -lHTForwardArray -lHTMicroball

SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

.PHONEY : all build
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all : build

build : HiRAEVTMapper.exe

HiRAEVTMapper.exe : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(CFLAGS) $(RLIBS)

install:
	@cp HiRAEVTMapper.exe $(HiRAEVTBIN)/${NAMEHIRAEVTMAPPEREXECUTABLE}

.PHONY: clean
clean :
	rm -f $(OBJS) HiRAEVTMapper.exe

.PHONY: distclean
distclean: clean
	@rm -f $(HiRAEVTBIN)/${NAMEHIRAEVTMAPPEREXECUTABLE}

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
