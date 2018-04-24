CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/HTMapper
INCLUDES  += -I$(HiRAEVTSRC)/logo
INCLUDES  += -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/HTExperimentalSetup
INCLUDES  += -I$(HiRAEVTSRC)/HTRawDataReader
INCLUDES  += -I$(HiRAEVTSRC)/HTRootElectronics
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap
INCLUDES  += -I$(HiRAEVTSRC)/detectors/HTDetector

RLIBS     := -L$(HiRAEVTLIB) -lHTLogo

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
	@cp HiRAEVTMapper.exe $(HiRAEVTBIN)/.

.PHONY: clean
clean :
	rm -f $(OBJS) HiRAEVTMapper.exe

.PHONY: distclean
distclean: clean
	@rm -f $(HiRAEVTBIN)/HiRAEVTMapper.exe

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
