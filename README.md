RIBbit2
===

Contributors: Daniele Dell'Aquila(1), Juan Manfredi, Zbigniew Chajecki

(1) dellaqui@nscl.msu.edu 

A full unpacker and data reduction program for the HiRA collaboration. The program consists in the following sub-programs:
 * RIBbitUnpacker : NSCL DAQ ROOT Unpacking software based on Juan Manfredi's RIBbit
 * RIBbitMapper : Reads data from ROOT TTrees created by RIBbitUnpacker to create fully mapped TTrees with detector definitions. The objects stored to the tree are optimized to make easier calibration and data reduction procedures
 * RIBbitAnalyzer : Introduces detector calibrations and pixellation/track recognition algorithms and create a final TTRee with physical data
 
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
* [The RIBbitUnpacker Program](#unpacker)
  * [Run the Code](#run-unpacker)
* [The RIBbitMapper Program](#mapper)
* [The RIBbitAnalyzer Program](#analyzer)
<!--te-->

## Getting the code
### Using git
The latest version of the code can be obtained by using the git command. This is possible after installing git on a linux machine (see https://git-scm.com/download/linux for further documentation on how to install git). Use the following command to download RIBbit2:
````
$ git clone https://github.com/dellaquilamaster/RIBbit2.git
````
### Downloading from Git Hub
The code can be downloaded also frm the Git Hub web page at the link: https://github.com/dellaquilamaster/RIBbit2, by
clicking on the "Clone or Download" button on the right side of the page and then "Download ZIP". It is possible to donwload also a previous release of the code. For a complete list of all the releases please visit: https://github.com/dellaquilamaster/RIBbit2/releases.
## Setup and Configuration
### Requirements
The code is compiled using the g++ compiler.
In order to compile and run the code ROOT 6 is required (the program has been tested with version 6.04.02). Please note that, since the program uses advanced ROOT 6 features, it is not possible to run or compile it by using an installation of ROOT 5. ROOT 6 is required when exporting environment variables (see section "Environment Variables").
### Environment Variables
Before compiling or running the code, it is required to export the needed environment variables and aliases. This can be done by launching, from the main folder of RIBbit2, the command:
````
$ source bin/RIBbit2.sh
````
Please note that the current version of the program requires ROOT6 and cannot be used under ROOT5 or previous versions. RIBbit2.sh is currently set to use ROOT-6.04.02, to change the ROOT version used please modify the variable ROOTVERSION in RIBbit2.sh.
### Compile the Code
To compile the code and make a clean installation use the sequence of commands:
````
$ make clean
$ make
$ make install
````
The binary file bin/RIBbitUnpacker.exe is generated in the compilation.
### Configure the program
The program can run over different experimental configurations (DAQ, detectors, ...) without be re-compiled. All the information needed can be configured from the file "config/RIBbit2.conf". This is the only file that the user has to change to configure the program. In the special language used to read the file, the character '\*' is used to provide a comment. Following a detailed list of the fields to configure:
* set RIBIT2_DIR : this command sets the directory of the RIBbit2 installation
* set RIBBIT2UNPACKER_SUMMARY_PATH : use this command to specify a folder to store the standard output of the unpacking process when the code is run in batch mode (i.e. ember or seaside)
* set RIBBIT2UNPACKER_ROOT_FILE_PATH : this command sets the location of the ROOT files obtained by RIBbit2Unpacker
* set EXPERIMENT_NAME : the name of the experiment (i.e. 15190)
* set EXPERIMENT_TITLE :
* set MERGED_DATA :
* set EVENT_FILE_PATH :
* FIRST_RUN :
* LAST_RUN :
* set EVENT_FILE_PATH :
* set DAQ_CONFIG :
* set PEDESTAL_VALUES :
* set CHANNEL_MAPPING :
## The RIBbitUnpacker Program
### Run the code
It is possible to interactively unpack a run or a group of runs by using the script bin/RIBbitUnpacker. To run the script and unpack a single run (looping over all the evt files) use the command (from the main RIBbit2 folder):
````
$ RIBbitUnpacker RUN_NUMBER
````
where RUN_NUMBER indicates the number of run to unpack. A group of runs can be unpacked by using:
````
$ RIBbitUnpacker FIRST_RUN LAST_RUN
````
where FIRST_RUN and LAST_RUN define the range of runs to unpack. Please note that if FIRST_RUN=LAST=RUN, the second command is equivalent to the first.
## The RIBbitMapper Program
The design and implementation of the program are in progress.
## The RIBbitAnalyzer Program
The program has to be designed.
