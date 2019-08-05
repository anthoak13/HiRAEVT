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

## Adding a detector the new way

This is an example for adding the detector type HTSimpleDetector. For a more thorough understanding, I suggest looking through the code for HTSimpleDetector, or HTNeutronWall for a more complicated detector structure. 

1. First create the minimum required classes
   - *HTSimpleDetector* with parent HTDetector
     This is the main detector class. It is responsible for creating the root tree output branch, building the events. It is also required to override the function InitMapping(). This function is called after an instance of the detector is created. It is responsible for creating the a detector map of the correct type. Usually the InitTreeBranch creates a branch with the type HTSimpleDetectorData. The `BuildEvent()` function will use the HTSimpleDetectorMap to pull in the correct data and store it in the correct place in HTSimpleDetectorData class described below.
   - *HTSimpleDetectorMap* with parent HTDetectorMap
     This class is responsible for knowing how modules and module channel numbers map to the actual detector elements. It also is reponsible for defining how to parse any map line in the mapping file that matches this detector name. The function `int ParseMapLine(const char *` int HTDetectorMap *must* be overriden by this class. How the format of a map line is left almost entirely up to the individual detector, with the only rule that is must start with the phrase "map detName" where detName is the name of the detector as defined by a define line in the map file.
   - *HTSimpleDetectorRootEvent* and *HTSimpleDetectorData*
     Both of these classes have historically been defined in the same header/source file. The HTSimpleDetectorRootEvent is in essence just a wrapper for the Data class. Honestly, I (Adam) am not convinced it is strictly necessary but I've kept it because Danielle had it and I didn't want to experiment with removing it. HTSimpleDetectorData is the class that is actually written out to the TTree. As such, the actual structure of the class definition (header file) is important for ROOT to build all of the surrounding infrastructure needed to read/write this class to a TTree. For full details on this process look at the [ROOT documentation](https://root.cern.ch/root/htmldoc/guides/users-guide/AddingaClass.html). The short version is you need to call the ClassDef(ClassName, version) macro at the end of this class. Root will try to decompse the class into leaves of primitive data types. You can also create variable length arrays that have a length defined on a run-by-run basis, if that length is also written to the tree. This is done in the comments on the same line as the decliration of the array. For example the code
     ```
     Int_t fMulti;
     Double_t fTime; //[fMulti]
     ```
     will create create two leaves. One an integer called fMulti, that hold the number of elements in the array fTime[fMulti].
   - Optionally: *HTSimpleDetectorCalibration* can be created to support the calibration function.

2. Create the LinkDef.h for the ROOT dictionary
   In order for ROOT to be able to use the data classes we've created a dictionary must be generated. This requires a LinkDef.h file. This is a file that tells the RootCling what to create a dictionary for. Along with a header gaurd it should contain two lines.
   ```
   #pragma link C++ class HTSimpleDetectorData+;
   #pragma link C++ class HTSimpleDetectorRootEvent+;
   
   ```
   If there are any other classes that ROOT needs to know about (maybe if the detector structure is more complicated, those can be added to this file.
   
3. The new detector must be added to the DetectorFactory
   To HTDetectorFactory.h in detectors/HTDetector/ add HTSimpleDetector.h to the list of included files. Then, to HTDetectorFactory.cxx in the `CreateDetector` class add an if statment to create a new instance of HTSimpleDetector.

4. Makefiles
   If desired, you can create the makefile from scratch, or just copy the onein HTSimpleDetector. This will build a shared library with the directory name.so. The naming convention described above has to be followed replacing HTSimpleDetector with whatever you named the detector. In addition to the makefile to create the library, in HiRAEVT/Makefile the detector must be added to all of the rules. 

5. Update documentation
   Add this new detector to the detector list on the README.md, and describe the mapping syntax.

## Program layout

### Mapper

The controling class is HTMapper. This class parses out the run number from the command line, and in the InitializeMapper function tells HTExperimentalInfo to get the associated HTRunInfo. This function then builds the ExperimentalSetup (ElectronicModules, Detectors, and DetectorMaps). Finally This function creates the output root tree, and inits the individual detector branches through HTExperimentalSetup.

The actual mapping happens in HTRawDataReader though, which has a pointer to the controlling HTMapper instance. This reader is then InitReader() and then ProcessRawTree() is called, where all of the work is done. InitReader, creates a TTreeReader and uses it to create TTreeReaders of the correct type for each electronic module. ProcessRawTree just loops through the TTreeReader and at each event if calls MapDetectors() and FillMapperEvent() on HTMapper. TODO: In reality I think this dependence should be swapped. HTMapper should own HTRawDataReader, not the other way around. It could be initialized in the InitializeMapper() method.

Each detector is responsible for knowing its own mapping. When the detctors are built, a detector is added to map fDetectors (string, *HTDetector). This new instnace is created by the HTDetectorFactory, and at this stage InitMapping() is called on each detector that creates a HTDetectorMap of the correct type. At the same time each module is also assigned to any detector that needs to know about it for mapping. This is stored internally by HTDetector. 