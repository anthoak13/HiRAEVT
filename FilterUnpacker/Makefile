
#INSTDIR=/usr/opt/nscldaq/11.0-rc12

#include $(INSTDIR)/filterkit/FilterIncludes
include $(RIBbitDAQROOT)/filterkit/FilterIncludes

#
#  Add your own compilation/link flags here:
RLIBS             := -L$(RIBbitLIB) -lRBElectronics -lRBExperiment -lRBSetup

INCLUDES  := -I$(RIBbitSRC)/
INCLUDES  += -I$(RIBbitSRC)/electronics

INCLUDES  += -I$(RIBbitSRC)/RBExperiment
INCLUDES  += -I$(RIBbitSRC)/RBSetup
#INCLUDES += -I/usr/opt/nscldaq/11.0-rc12/filterkit/FilterIncludes

USERCXXFLAGS = -g $(INCLUDES) $(RLIBS)
USERCCFLAGS  = $(USERCXXFLAGS)
USERLDFLAGS  = -g $(INCLUDES) $(RLIBS) $(shell root-config --libs)

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

build : UnpackerFilter

install:
	@cp UnpackerFilter $(RIBbitBIN)/.
	@cp gofilter $(RIBbitBIN)/.

clean :
	rm -f $(OBJECTS) Unpacker.o UnpackerFilter

distclean: clean
	@rm -f $(RIBbitBIN)/UnpackerFilter
	@rm -f $(RIBbitBIN)/gofilter


# Build this separately and then link in later
#Unpacker.o : Unpacker.cpp
#	$(CXX) -g $(USERCXXFLAGS) $(LDFLAGS) -c $(shell root-config --cflags) -o $@ $< $(shell root-config --libs)

#UnpackerFilter : $(OBJECTS) Unpacker.o
#	$(CXX) -g -o $@ $(USERLDFLAGS) $(LDFLAGS) -Wl,-rpath=$(INSTDIR)  FragmentIndex.o SkeletonMain.o CUnpackerFilter.o Unpacker.o


# Build this separately and then link in later
Unpacker.o : Unpacker.cpp
	$(CXX) -g $(USERCXXFLAGS) $(LDFLAGS) -c $(shell root-config --cflags) -o $@ $< $(shell root-config --libs)

UnpackerFilter : $(OBJECTS) Unpacker.o
	$(CXX) -g $(OBJECTS) Unpacker.o -o $@ $(USERLDFLAGS) $(LDFLAGS) -Wl,-rpath=$(INSTDIR)
