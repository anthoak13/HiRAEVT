HiRAEVT
===

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
  * [Configure the Program](#configure)
* [The HiRAEVTUnpacker Program](#unpacker)
  * [Run the Code](#run-unpacker)
  * [Output Data](#output-unpacker)
  * [User Summary Information](#userinfo-unpacker)
* [The HiRAEVTMapper Program](#mapper)
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
The binary file bin/HiRAEVTUnpacker.exe is generated in the compilation.
### Configure the program
The program can run over different experimental configurations (DAQ, detectors, ...) without be re-compiled. All the information needed can be configured from the file "config/RIBbit2.conf". This is the only file that the user has to change to configure the program. In the special language used to read the file, the character '\*' is used to provide a comment. Following a detailed list of the fields to configure:
* set HiRAEVT_DIR : this command sets the directory of the RIBbit2 installation
* set HiRAEVTUNPACKER_SUMMARY_PATH : use this command to specify a folder to store the standard output of the unpacking process when the code is run in batch mode (i.e. ember or seaside)
* set HiRAEVTUNPACKER_ROOT_FILE_PATH : this command sets the location of the ROOT files obtained by HiRAEVTUnpacker
* set EXPERIMENT_NAME : the name of the experiment (i.e. 15190)
* set EXPERIMENT_TITLE : a generic title to describe the experiment
* set MERGED_DATA : this command can be "true" if data is merged or "false" if data is not merged
* set EVENT_FILE_PATH : this command sets the path of the evt files. This path can be also set for individual group of runs by using the flag --run=FIRST_RUN-LAST-RUN. The flag --exclude=RUN1,RUN2,...,RUNN can be used to exclude a group of runs, namely 1,..., N, from this setting.
* FIRST_RUN : this is the first run of the whole experiment
* LAST_RUN : this is the last run of the whole experiment (the unpacker won't unpack runs after LAST_RUN)
* set DAQ_CONFIG : set the DAQ config (see the input-file folder, which contains an example of daqconfig file well commented). This command supports the --run and --exclude flags.
* set PEDESTAL_VALUES : set pedestal values for electronic channels. This command supports the --run and --exclude flags.
* set CHANNEL_MAPPING : define detectors and set mapping. This command supports the --run and --exclude flags.
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
### Output Data
Output data is stored in a tree called EXXXXX, where XXXXX represents the experiment name (i.e. E15190). The folder where the tree is stored is configured in the config file (see section "Configure the Program").
### User Summary Information
Useful user information and a general unpacking summary can be retrieved from the tree by using the following command after opening the tree with ROOT:
````
$ EXXXXX->GetUserInfo()
````
Where EXXXXX represents the TTree key with which the tree is saved on the file or a pointer to the TTree object retrieved from the file. Interactively, one can easily print those information via the command:
````
$ EXXXXX->GetUserInfo()->Print()
````
## The HiRAEVTMapper Program
The design and implementation of the program are in progress.
## The HiRAEVTAnalyzer Program
The program has to be designed.
