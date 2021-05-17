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

## Setup and Configuration

### Requirements
The following are required to use the code and must be configured by the user:

* g++ compiler with c++14 feature supports
* CMake version 3.11 or higher
* [FairRoot](https://github.com/FairRootGroup/FairRoot) version 18.00 or higher
  * In the future this will be an optional dependence if [ROOT](https://root.cern/) v16.20 or higher is installed
* [NSCL DAQ](http://docs.nscl.msu.edu/daq/)

The following are requirements of the code, and will be downloaded and configured using cmake:

* [nlohmann's JSON library](https://github.com/nlohmann/json) which is dowloaded and configured using CMake.

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
