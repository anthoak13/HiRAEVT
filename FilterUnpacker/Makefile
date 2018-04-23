#include $(INSTDIR)/filterkit/FilterIncludes
include $(HiRAEVTDAQROOT)/filterkit/FilterIncludes
#
#  Add your own compilation/link flags here:
RLIBS     := -L$(HiRAEVTLIB) -lRBElectronics -lRBExperiment -lRBSetup -lHTLogo -lHTShared -lHTRunInfo

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  += -I$(HiRAEVTSRC)/electronics
INCLUDES  += -I$(HiRAEVTSRC)/RBExperiment
INCLUDES  += -I$(HiRAEVTSRC)/RBSetup
INCLUDES  += -I$(HiRAEVTSRC)/logo
INCLUDES  += -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/HTRunInfo
INCLUDES  += -I$(HiRAEVTSRC)/FilterUnpacker

CFLAGS    :=`root-config --cflags --libs`
CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 $(RLIBS)

#
#  Add the names of objects you need here if you modified the name of the driver file,
#  this should also reflect thtat.
#

OBJECTS = FragmentIndex.o CUnpackerFilter.o SkeletonMain.o

#
#  Modify the line below to provide the name of the library you are trying to build
#  it must be of the form libsomethingorother.so
#


.PHONEY : all build

all : build

build : HiRAEVTUnpacker.exe

install:
	@cp HiRAEVTUnpacker.exe $(HiRAEVTBIN)/.
	@cp gofilter $(HiRAEVTBIN)/.

clean :
	rm -f $(OBJECTS) Unpacker.o HiRAEVTUnpacker.exe

distclean: clean
	@rm -f $(HiRAEVTBIN)/HiRAEVTUnpacker.exe
	@rm -f $(HiRAEVTBIN)/gofilter

# Build this separately and then link in later
Unpacker.o : Unpacker.cpp
	$(CXX) $(CXXFLAGS) $(USERCXXFLAGS) $(LDFLAGS) -c $(shell root-config --cflags) -o $@ $< $(CFLAGS)

HiRAEVTUnpacker.exe : $(OBJECTS) Unpacker.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) Unpacker.o -o $@ $(USERLDFLAGS) $(LDFLAGS) $(CFLAGS) -Wl,-rpath=$(INSTDIR)
