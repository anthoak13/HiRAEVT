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
