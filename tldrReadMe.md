## Intro
This tldr readme assumes that the code is being run on fishtank at the NSCL. It uses root v6.04 which is compiled with c++11 features and gnu g++ version 4.9.2

## Getting the code
Checkout the code using git from
```
git clone https://github.com/nscl-hira/HiRAEVT.git
```

## Setup and Configuration
Before compiling or running the code, you first need to setup the enviromental variables used by the code. This is done by
```
$ source bin/HiRAEVT.sh
```
This sets the correct version of root and pulls in the expirement information from config/HiRAEVT.conf. The config file can be changed by editing the line `export HiRAEVTCONFIG=config/HiRAEVT.conf` in bin/HiRAEVT.sh

### Compiling
To compile the code and make a clean installation use the sequence of commands:
```
$ make clean
$ make
$ make install
```
The binary files bin/HiRAEVTUnpacker.exe bin/HiRAEVTMapper.exe are generated in the compilation.

### Configuration
For a description of the configuration file and how to setup and expirement see the full readme

## HiRAEVTUnpacker
The HiRAEVTUnpacker takes raw evt files and converts them into a ROOT Tree stucture. Each module in the DAQ is given its own branch of the tree. The tree is named

### Running the code
It is possible to unpack a run or a group of runs by using the script bin/HiRAEVTUnpacker. To unpack a single run (looping over all the evt files) use the command (from the main HiRAEVT folder):
````
$ HiRAEVTUnpacker RUN_NUMBER
````
where RUN_NUMBER indicates the number of run to unpack. A group of runs can be unpacked by using:
````
$ HiRAEVTUnpacker FIRST_RUN LAST_RUN
````
where FIRST_RUN and LAST_RUN define the range of runs to unpack.

### Getting the data

## Adding a new detector

To add a new detector there a number of classes that need to be defined. First a detector class must be created that extends HTDetector. This subclass is responsible for writing the functions `InitTreeBranch(TTree *)`, `BuildEvent()`, and `FillMappedData()`. This esentially defines the behavior of the class.

In general, each detector has an associated data type. For example, the ion chamber has detector class `HTIonChamber` with associated data type `HTIonChamberData`. The tree branch associated with this detector is then an instance of this data type.

In order to get this to work, there is also an associate RootEvent class (HTIonChamberRootEvent) that is defined in the same header file. This is just a class to hold an instance of the Data class to write to the tree

The module has to be added to the long if statment list in HTExperimentalSetup. The header file has to be included here as well. Becuase of how the make file is written you also have to manually add the directory with the detector header file HTIonChmber.h to the make files in directories HTExperimentalSetup, HTMapper, HTRawDataReader. To the HTMapper make file, you also have to add the library flag -lHTIonChamber. To the main Makefile, you have to add the lines to build and install the detector.

Because the root electronics module was never created for the MADC, I had to write it. Basically I just coppied the CAEN7xx and changed the name. This class also had to be added to the long if statment list in HTExpirementalSetup::BuildElectronicModules.

The HTIonChamberMap class also has to be created and added to the long if statment list in HTExperimentalSetup::BuildDetectorMaps(). *What is the difference between adding the map to fDetectorMaps and the second part of TheDetector?*

