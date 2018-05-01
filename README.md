HiRAEVT
===
HiRA Extremely Versatile Tool (for Unpacking and Reduction of experiment Data)

Contributors: Daniele Dell'Aquila(1), Juan Manfredi, Zbigniew Chajecki

(1) dellaqui@nscl.msu.edu 

A full unpacker and data reduction program for the HiRA collaboration. The program consists in the following sub-programs:
 * HiRAEVTUnpacker : NSCL DAQ ROOT Unpacking software based on Juan Manfredi's RIBbit
 * HiRAEVTMapper : Reads data from ROOT TTrees created by RIBbitUnpacker to create fully mapped TTrees with detector definitions. The objects stored to the tree are optimized to make easier calibration and data reduction procedures
 * HiRAEVTAnalyzer : Introduces detector calibrations and pixellation/track recognition algorithms and create a final TTRee with physical data
 
The aim of the software is obtaining a sistematic and reliable procedure for each of the steps of the data analysis process for an NSCL HiRA group experiment: data unpacking > data mapping > calibrations and physics.

# Useful links:
  * [NSCL DAQ](http://docs.nscl.msu.edu/daq/) : NSCL Data Acquisition (DAQ) documentation
  * [HiRA Webpage](https://groups.nscl.msu.edu/hira/) : High Resolution Array (HiRA) group website
  
Table of contents
=================
<!--ts-->
* [Getting the code](#getting-the-code)
  * [Using git](#using-git)
  * [Downloading from Git Hub](#downloading-from-git-hub)
* [Setup and Configuration](#setup)
  * [Requirements](#requirements)
  * [Environment Variables](#env-variables)
  * [Compile the Code](#compilation)
  * [Compile the Code on NSCL ember or seaside](#compilation-nscl)
  * [Configure the Program](#configure)
  * [Limitations](#limitations)
* [The HiRAEVTUnpacker Program](#unpacker)
  * [Run the Code](#run-unpacker)
  * [Run the Code on NSCL ember or seaside](#run-nscl-unpacker)
  * [Output Data](#output-unpacker)
  * [User Summary Information](#userinfo-unpacker)
  * [Notes for Developers](#dev-unpacker)
* [The HiRAEVTMapper Program](#mapper)
  * [Run the Code](#run-mapper)
  * [Run the Code on NSCL ember or seaside](#run-nscl-mapper)
  * [Output Data](#output-mapper)
  * [Notes for Developers](#dev-mapper)
* [The HiRAEVTAnalyzer Program](#analyzer)
<!--te-->

## Getting the code
### Using git
The latest version of the code can be obtained by using the git command. This is possible after installing git on a linux machine (see https://git-scm.com/download/linux for further documentation on how to install git). Use the following command to download RIBbit2:
````
$ git clone https://github.com/dellaquilamaster/HiRAEVT.git
````
### Downloading from Git Hub
The code can be downloaded also frm the Git Hub web page at the link: https://github.com/dellaquilamaster/HiRAEVT, by
clicking on the "Clone or Download" button on the right side of the page and then "Download ZIP". It is possible to donwload also a previous release of the code. For a complete list of all the releases please visit: https://github.com/dellaquilamaster/HiRAEVT/releases.
## Setup and Configuration
### Requirements
The code is compiled using the g++ compiler.
In order to compile and run the code ROOT 6 is required (the program has been tested with version 6.04.02). Please note that, since the program uses advanced ROOT 6 features, it is not possible to run or compile it by using an installation of ROOT 5. ROOT 6 is required when exporting environment variables (see section "Environment Variables").
### Environment Variables
Before compiling or running the code, it is required to export the needed environment variables and aliases. This can be done by launching, from the main folder of HiRAEVT, the command:
````
$ source bin/HiRAEVT.sh
````
Please note that the current version of the program requires ROOT6 and cannot be used under ROOT5 or previous versions. HiRAEVT.sh is currently set to use ROOT-6.04.02, to change the ROOT version used please modify the variable ROOTVERSION in HiRAEVT.sh.
### Compile the Code
To compile the code and make a clean installation use the sequence of commands:
````
$ make clean
$ make
$ make install
````
The binary files bin/HiRAEVTUnpacker.exe bin/HiRAEVTMapper.exe are generated in the compilation.
### Compile the Code on NSCL ember or seaside
The code can be independently compiled on the NSCL clusters ember or seaside. A compilation under ember or seaside does not erase a previous compilation under a third machine. Compiling the code on ember or seaside will generate, respectively, the bineary files bin/HiRAEVTUnpackerEmber.exe bin/HiRAEVTMapperEmber.exe or bin/HiRAEVTUnpackerSeaside.exe bin/HiRAEVTMapperSeaside.exe.

WARNING: it is temporarly not possible to compile and run the program from NSCL seaside. It will be soon possible after the ROOT version will be updated to 6.
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
* set EVENT_FILE_PATH : this command sets the path of the evt files. This path can be also set for individual group of runs by using the flag --run=FIRST_RUN-LAST-RUN. The flag --exclude=RUN1,RUN2,...,RUNN can be used to exclude a group of runs, namely 1,..., N, from this setting.
* FIRST_RUN : this is the first run of the whole experiment
* LAST_RUN : this is the last run of the whole experiment (the unpacker won't unpack runs after LAST_RUN)
* set DAQ_CONFIG : set the DAQ config (see the input-file folder, which contains an example of daqconfig file well commented). This command supports the --run and --exclude flags.
* set PEDESTAL_VALUES : set pedestal values for electronic channels. This command supports the --run and --exclude flags.
* set CHANNEL_MAPPING : define detectors and set mapping. This command supports the --run and --exclude flags.
### Limitations
The code is explicitly designed to by a highly versatile tool. Anyway, some limitations are present (and maybe more limitations will be found in the future in more specific cases):
 - The code needs to be launched from the program main folder;
 - The class RBSisTimestamp is specificallu designed for the timestamp configuration used in e15190.
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

WARNING: it is temporarly not possible to compile and run the program from NSCL seaside. It will be soon possible after the ROOT version will be updated to 6.
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

WARNING: it is temporarly not possible to compile and run the program from NSCL seaside. It will be soon possible after the ROOT version will be updated to 6.
### Output Data
Output data is stored in a tree called EXXXXX, where XXXXX represents the experiment name (i.e. E15190). The folder where the tree is stored is configured in the config file by setting HiRAEVTMAPPER_ROOT_FILE_PATH in the configuration file (see section "Configure the Program").

The structure of the output tree is constituted by an individual branch for each detector defined in the mapping file. In the presence of an "HiRA" detector, a sub-branch will be created for each telescope.
## Notes for Developers
 -The mapping of HiRA strips does not occour in a "channel-by-channel" philosophy, but individual blocks of channels (namely DE, EF, EB), belonging to a single physical detector, are mapped to a unique specific motherboard(bank) and chipboard. For this reason, an algorithm used to produce (telescope, motherboard, chip, channel) -> (strip). Any future changes of the algorithm should be made to the method int HTHiRAMap::ParseMapLine(const char *).
## The HiRAEVTAnalyzer Program
The program has to be designed.
