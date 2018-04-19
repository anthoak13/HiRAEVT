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
* [The RIBbitUnpacker Program](#unpacker)
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
### 
## The RIBbitUnpacker Program
## The RIBbitMapper Program
The design and implementation of the program are in progress
## The RIBbitAnalyzer Program
The program has to be designed
