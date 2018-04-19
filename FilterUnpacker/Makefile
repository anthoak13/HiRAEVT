#include $(INSTDIR)/filterkit/FilterIncludes
include $(RIBbitDAQROOT)/filterkit/FilterIncludes
#
#  Add your own compilation/link flags here:
RLIBS     := -L$(RIBbitLIB) -lRBElectronics -lRBExperiment -lRBSetup -lRBLogo -lRBShared -lRBRunInfo

INCLUDES  := -I$(RIBbitSRC)/
INCLUDES  += -I$(RIBbitSRC)/electronics
INCLUDES  += -I$(RIBbitSRC)/RBExperiment
INCLUDES  += -I$(RIBbitSRC)/RBSetup
INCLUDES  += -I$(RIBbitSRC)/logo
INCLUDES  += -I$(RIBbitSRC)/shared
INCLUDES  += -I$(RIBbitSRC)/RBRunInfo
INCLUDES  += -I$(RIBbitSRC)/FilterUnpacker

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

build : RIBbitUnpacker.exe

install:
	@cp RIBbitUnpacker.exe $(RIBbitBIN)/.
	@cp gofilter $(RIBbitBIN)/.

clean :
	rm -f $(OBJECTS) Unpacker.o RIBbitUnpacker.exe

distclean: clean
	@rm -f $(RIBbitBIN)/RIBbitUnpacker.exe
	@rm -f $(RIBbitBIN)/gofilter

# Build this separately and then link in later
Unpacker.o : Unpacker.cpp
	$(CXX) $(CXXFLAGS) $(USERCXXFLAGS) $(LDFLAGS) -c $(shell root-config --cflags) -o $@ $< $(CFLAGS)

RIBbitUnpacker.exe : $(OBJECTS) Unpacker.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) Unpacker.o -o $@ $(USERLDFLAGS) $(LDFLAGS) $(CFLAGS) -Wl,-rpath=$(INSTDIR)
