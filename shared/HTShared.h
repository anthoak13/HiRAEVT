#ifndef HTSHARED_H
#define HTSHARED_H

class Unpacker;
class RBExperiment;
class HTRunInfo;

//Global variables
extern Unpacker * gUnpacker;
extern RBExperiment * gExperiment;
extern HTRunInfo * gRun;

//Constants ********************************************************
// HiRA Constants
extern const int N_STRIPS_PER_TELESCOPE;
extern const int N_CSIS_PER_TELESCOPE;
extern const int N_HINP_BANKS;
extern const int N_HINP_CHIP_PER_CHIPBOARD;
extern const int N_HINP_CHIPS_PER_BANK;
extern const int N_HINP_CHANNELS_PER_CHIP;
// Microball Constants
/* WARNING: uBall number of rings and detectors per ring is fixed */
extern const int N_MICROBALL_RINGS;
extern const int N_MICROBALL_DETS_PER_RING[];
extern const int TOT_NUMER_MICROBALL_DETECTORS;
/******************************************************************/

#endif
