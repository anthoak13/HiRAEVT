#include <HTShared.h>

//Global variables
HTRunInfo* gRun;

//Constants ********************************************************
// HiRA Constants
const int N_STRIPS_PER_TELESCOPE = 32;
const int N_CSIS_PER_TELESCOPE = 4;
const int N_HINP_BANKS = 2;
const int N_HINP_CHIP_PER_CHIPBOARD = 2;
const int N_HINP_CHIPS_PER_BANK = 28;
const int N_HINP_CHANNELS_PER_CHIP = 16;
// Microball Constants
const int N_MICROBALL_RINGS = 9;
const int N_MICROBALL_DETS_PER_RING[] = {6, 10, 12, 12, 14, 14, 12, 10, 6};
const int TOT_NUMER_MICROBALL_DETECTORS = 96;
/******************************************************************/
