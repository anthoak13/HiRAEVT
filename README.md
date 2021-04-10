HiRAEVT
===
[HiRA](https://groups.nscl.msu.edu/hira/) Extremely Versatile Tool (for Unpacking and Reduction of experiment Data)

Contributors: Adam Anthony(1), Daniele Dell'Aquila(2), Juan Manfredi, Zbigniew Chajecki

(1) anthonya@frib.msu.edu
(2) dellaqui@nscl.msu.edu 

This might be out of date. The program is undergoing a update so it can integrate gracefully with other analysis programs as well as work as a standalone program. In particular it is being moved to a CMake project so it can be required by other CMake projects. In particular, this is being done to ease analysis of AT-TPC experiments that are analyized using [ATTPCROOT](https://github.com/ATTPC/ATTPCROOTv2) and detectors read out using the [NSCL DAQ](http://docs.nscl.msu.edu/daq/).

A full unpacker and data reduction program for the HiRA collaboration. The program consists in the following sub-programs:
 * HiRAEVTUnpacker : NSCL DAQ ROOT Unpacking software based on Juan Manfredi's RIBbit
 * HiRAEVTMapper : Reads data from ROOT TTrees created by RIBbitUnpacker to create fully mapped TTrees with detector definitions. The objects stored to the tree are optimized to make easier calibration and data reduction procedures
 
The aim of the software is obtaining a sistematic and reliable procedure for each of the steps of the data analysis process for an NSCL HiRA group experiment: data unpacking > data mapping > calibrations and physics.
  
Table of contents
=================
<!--ts-->
* [Setup and Configuration](#setup-and-configuration)
  * [Requirements](#requirements)
  * [Environment Variables](#environment-variables)
  * [Compile the Code](#compile-the-code)
  * [Compile the Code on NSCL ember or seaside](#compile-the-code-on-nscl-ember-or-seaside)
  * [Configure the Program](#configure-the-program)
  * [Limitations](#limitations)
* [The HiRAEVTUnpacker Program](#the-hiraevtunpacker-program)
  * [Run the Code](#run-the-code)
  * [Run the Code on NSCL ember or seaside](#run-the-code-on-nscl-ember-or-seaside)
  * [Output Data](#output-data)
  * [User Summary Information](#user-summary-information)
  * [Notes for Developers](#notes-for-developers)
* [The HiRAEVTMapper Program](#the-hiraevtmapper-program)
  * [Run the Code](#run-the-code)
  * [Run the Code on NSCL ember or seaside](#run-the-code-on-nscl-ember-or-seaside)
  * [Output Data](#output-data)
  * [Notes for Developers](#notes-for-developers)
* [The HiRAEVTAnalyzer Program](#the-hiraevtanalyzer-program)
<!--te-->

### Working notes

* Folders that compile to an executable
  * [ ] FilterUnpacker
  * [ ] HTMapper
 
* Folders that compile to a library (check a bunch of these to remove uneeded lnkdefs and list of detectors)
  * [x] HTDetectors
  * [x] HTElectronics
  * [x] HTExperiment
  * [x] HTExperimentalSetup (need to edit so it doesn't know about every detector)
  * [x] HTRawDataReader
  * [x] HTRootElectronics
  * [x] HTRunInfo


## Setup and Configuration

### Requirements
The following are required to use the code:

* g++ compiler with c++14 feature supports
* CMake version 3.10 or higher
* [FairRoot](https://github.com/FairRootGroup/FairRoot) version 18.00 or higher
  * In the future this will be an optional dependence if [ROOT](https://root.cern/) v16.20 or higher is installed
* [NSCL DAQ](http://docs.nscl.msu.edu/daq/)

NB: For users on the FRIB cluster, fishtank. After the recent move to using singularity containers, the NSCLDAQ files are only accesable if you source `/usr/opt/buster.sh`.

### Building the Code
To compile the code, all of the above programs need to be installed and they need to be discoverable by CMake `find_module`. If they were installed in a typical maner, this should not be a problem. The exception to this is NSCLDAQ which needs its header files to be installed at the location `/usr/opt/nscldaq/current/include`. 

To compile the code, create a build directory and configure cmake to build out of source
````
$ cd [build dir]
$ cmake [source dir]
$ make
````
This will configure cmake, and build the program.


### Configure the program
The program can run over different experimental configurations (DAQ, detectors, ...) without be re-compiled. All the information needed can be configured from the file "config/RIBbit2.conf". This is the only file that the user has to change to configure the program. In the special language used to read the file, the character '\*' is used to provide a comment. Following a detailed list of the fields to configure:
* set HiRAEVT_DIR : this command sets the directory of the RIBbit2 installation
* set HiRAEVTUNPACKER_SUMMARY_PATH : use this command to specify a folder to store the standard output of the unpacking process (HiRAEVTUnpacker) when the code is run in batch mode (i.e. ember or seaside)
* set HiRAEVTUNPACKER_ROOT_FILE_PATH : this command sets the location of the ROOT files obtained by HiRAEVTUnpacker
* set HiRAEVTMAPPER_SUMMARY_PATH : use this command to specify a folder to store the standard output of the mapping process (HiRAEVTMapper) when the code is run in batch mode (i.e. ember or seaside)
* set HiRAEVTMAPPER_ROOT_FILE_PATH : this command sets the location of the ROOT files obtained by HiRAEVTMapper
* set EXPERIMENT_NAME : the name of the experiment (i.e. 15190)
* set EXPERIMENT_TITLE : a generic title to describe the experiment
* set MERGED_DATA : this command can be "true" if data is merged or "false" if data is not merged
* set EVENT_FILE_PATH : this command sets the path of the evt files. This path can be also set for individual group of runs by using the flag --run=FIRST_RUN-LAST_RUN or a list of individual runs --run=RUN1,RUN2,RUN3,... etc. The flag --exclude=RUN1,RUN2,...,RUNN can be used to exclude a group of runs, namely 1,..., N, from this setting. Note that more than one --run and --exclude option can be set per configuration line, but each --run option must have OR a range of runs OR a list of run, no combinations are allowed. Spaces are not allowed within each option.
* FIRST_RUN : this is the first run of the whole experiment
* LAST_RUN : this is the last run of the whole experiment (the unpacker won't unpack runs after LAST_RUN)
* set DAQ_CONFIG : set the DAQ config (see the input-file folder, which contains an example of daqconfig file well commented). This command supports the --run and --exclude flags.
* set PEDESTAL_VALUES : set pedestal values for electronic channels. This command supports the --run and --exclude flags.
* set CHANNEL_MAPPING : define detectors and set mapping. This command supports the --run and --exclude flags.

### Limitations
The code is explicitly designed to by a highly versatile tool. Anyway, some limitations are present (and maybe more limitations will be found in the future in more specific cases):
 - The code needs to be launched from the program main folder;
 - The class RBSisTimestamp is specifically designed for the timestamp configuration used in e15190.

## The HiRAEVTUnpacker Program

### Run the code
It is possible to interactively unpack a run or a group of runs by using the script bin/RIBbitUnpacker. To run the script and unpack a single run (looping over all the evt files) use the command (from the main HiRAEVT folder):
````
$ HiRAEVTUnpacker RUN_NUMBER
````
where RUN_NUMBER indicates the number of run to unpack. A group of runs can be unpacked by using:
````
$ HiRAEVTUnpacker FIRST_RUN LAST_RUN
````
where FIRST_RUN and LAST_RUN define the range of runs to unpack. Please note that if FIRST_RUN=LAST=RUN, the second command is equivalent to the first.

### Run the Code on NSCL ember or seaside
The program is designed to run interactively on NSCL fishtank-like machines or interactively or in batch on NSCL clusters like ember or seaside. The above mentioned commands work in the same way when one wants to launch the program interactively on ember or seaside. When on ember or seaside, the program can be also launched in batch mode, respectively using SLURM or PBS queue systems.
To launch the program with SLURM batch mode in ember use the command:
````
$ HiRAEVTUnpackerEmber RUN_NUMBER
````
This works for a single run (RUN_NUMBER). For a group of runs FIRST_RUN~LAST_RUN instead use the command:
````
$ HiRAEVTUnpackerEmber FIRST_RUN LAST_RUN
````
Analogous commands can be used to launch the program in seaside by using PBS queue system:
````
$ HiRAEVTUnpackerSeaside RUN_NUMBER
````
This works for a single run (RUN_NUMBER). For a group of runs FIRST_RUN~LAST_RUN instead use the command:
````
$ HiRAEVTUnpackerSeaside FIRST_RUN LAST_RUN
````
When the program is launched in batch mode, the video output is saved in a summary file, whose location can be configured by setting HiRAEVTUNPACKER_SUMMARY_PATH in the configuration file (see section "Configure the Program"). The summary files are individually named by including run number and evt file number.

**_WARNING_**: it is temporarly not possible to compile and run the program from NSCL seaside. It will be soon possible after the ROOT version will be updated to 6.

### Output Data
Output data is stored in a tree called EXXXXX, where XXXXX represents the experiment name (i.e. E15190). The folder where the tree is stored is configured in the config file by setting HiRAEVTUNPACKER_ROOT_FILE_PATH in the configuration file (see section "Configure the Program").

### User Summary Information
Useful user information and a general unpacking summary can be retrieved from the tree by using the following command after opening the tree with ROOT:
````
$ EXXXXX->GetUserInfo()
````
Where EXXXXX represents the TTree key with which the tree is saved on the file or a pointer to the TTree object retrieved from the file. Interactively, one can easily print those information via the command:
````
$ EXXXXX->GetUserInfo()->Print()
````
## Notes for Developers
## The HiRAEVTMapper Program
### Run the code
It is possible to interactively unpack a run or a group of runs by using the script bin/RIBbitUnpacker. To run the script and unpack a single run (looping over all the evt files) use the command (from the main HiRAEVT folder):
````
$ HiRAEVTMapper RUN_NUMBER
````
where RUN_NUMBER indicates the number of run to unpack. A group of runs can be unpacked by using:
````
$ HiRAEVTMapper FIRST_RUN LAST_RUN
````
where FIRST_RUN and LAST_RUN define the range of runs to unpack. Please note that if FIRST_RUN=LAST=RUN, the second command is equivalent to the first.

### Run the Code on NSCL ember or seaside
The program is designed to run interactively on NSCL fishtank-like machines or interactively or in batch on NSCL clusters like ember or seaside. The above mentioned commands work in the same way when one wants to launch the program interactively on ember or seaside. When on ember or seaside, the program can be also launched in batch mode, respectively using SLURM or PBS queue systems.
To launch the program with SLURM batch mode in ember use the command:
````
$ HiRAEVTMapperEmber RUN_NUMBER
````
This works for a single run (RUN_NUMBER). For a group of runs FIRST_RUN~LAST_RUN instead use the command:
````
$ HiRAEVTMapperEmber FIRST_RUN LAST_RUN
````
Analogous commands can be used to launch the program in seaside by using PBS queue system:
````
$ HiRAEVTMapperSeaside RUN_NUMBER
````
This works for a single run (RUN_NUMBER). For a group of runs FIRST_RUN~LAST_RUN instead use the command:
````
$ HiRAEVTMapperSeaside FIRST_RUN LAST_RUN
````
When the program is launched in batch mode, the video output is saved in a summary file, whose location can be configured by setting HiRAEVTMAPPER_SUMMARY_PATH in the configuration file (see section "Configure the Program"). The summary files are individually named by including run number.

**_WARNING_**: it is temporarly not possible to compile and run the program from NSCL seaside. It will be soon possible after the ROOT version will be updated to 6.

### Output Data
Output data is stored in a tree called EXXXXX, where XXXXX represents the experiment name (i.e. E15190). The folder where the tree is stored is configured in the config file by setting HiRAEVTMAPPER_ROOT_FILE_PATH in the configuration file (see section "Configure the Program").

The structure of the output tree is constituted by an individual branch for each detector defined in the mapping file. In the presence of an "HiRA" detector, a sub-branch will be created for each telescope. For convenience, timestamp and TDC spare channels are treated like detectors. The second can map (see the map file contained in the folder "input") individual TDC channels that are used as benchmark, containing for example experiment triggers.
Here a summary of the data structures for each individual detector:

**_HiRA_**  
|- **fDE**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumstrip\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyHi\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyLo\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fTime\[fmulti\]  
|- **fEF**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumstrip\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyHi\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyLo\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fTime\[fmulti\]  
|- **fEB**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumstrip\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyHi\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fEnergyLo\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ UShort_t fTime\[fmulti\]  
|- **fCsI**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumcsi\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fEnergy\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fTime\[fmulti\]  
**_NeutronWall_**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumbar\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fLeft\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fRight\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fFastLeft\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fFastRight\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fTimeLeft\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fTimeRight\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fGeoMean\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fFastGeoMean\[fmulti\]  
**_VetoWall_**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumbar\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fBottom\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fTop\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fTimeBottom\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Double_t fTimeTop\[fmulti\]  
**_ForwardArray_**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumdet\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fEnergy\[fmulti\]  
**_Microball_**  
|&nbsp;&nbsp;&nbsp;+ int fmulti  
|&nbsp;&nbsp;&nbsp;+ int fnumring\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ int fnumdet\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fTail\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fFast\[fmulti\]  
|&nbsp;&nbsp;&nbsp;+ Short_t fTime\[fmulti\]  
**_HTSisTimestampe15190_**  
|&nbsp;&nbsp;&nbsp;+ Long64_t fTimestamp  
|&nbsp;&nbsp;&nbsp;+ Long64_t fTimestampKoreans  
**_HTTDCSpare_**  
|&nbsp;&nbsp;&nbsp;+ Double_t (...)  

## Notes for Developers
 - The mapping of HiRA strips does not occour in a "channel-by-channel" philosophy, but individual blocks of channels (namely DE, EF, EB), belonging to a single physical detector, are mapped to a unique specific motherboard(bank) and chipboard. For this reason, an algorithm is used to produce (telescope, motherboard, chip, channel) -> (strip) associations. Any future changes of the algorithm should be made to the method int HTHiRAMap::ParseMapLine(const char \*).
 - Despite the output tree and related structures contain a branch for the DE stage of HiRA (Single Sided Silicon Strip Detector), mapping algorithms and maps have to be implemented. For a future extension of the program features to this detection stage the following files have to be modified: detectors/HTHiRA.cxx HTDetectorMap/HTHiRAMap.h HTDetectorMap/HTHiRAMap.cxx.
