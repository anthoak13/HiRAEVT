RIBbit2
===

Contributors: Daniele Dell'Aquila, Juan Manfredi, Zbigniew Chajecki

A full unpacker and data reduction program for the HiRA collaboration. The program consists in the following sub-programs:
 * RIBbitUnpacker : NSCL DAQ ROOT Unpacking software based on Juan Manfredi's RIBbit
 * RIBbitMapper : Reads data from ROOT TTrees created by RIBbitUnpacker to create fully mapped TTrees with detector definitions. The objects stored to the tree are optimized to make easier calibration and data reduction procedures
 * RIBbitAnalyzer : Introduces detector calibrations and pixellation/track recognition algorithms and create a final TTRee with physical data

# Useful links:
  * [nscl_daq](http://docs.nscl.msu.edu/daq/) : NSCL Data Acquisition (DAQ) documentation
  * [hira webpage](https://groups.nscl.msu.edu/hira/) : High Resolution Array (HiRA) group website
  
# Contents
1. [Getting the code](#getting-the-code)
  1. [Using git](#using-git)
  2. [Downloading from Git Hub](#downloading-from-git-hub)
2. [Setup](#setup)
  1. [Requirements](#requirements)

## Getting the code
### Using git
