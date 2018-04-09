//#define DEBUG                                   // Output primary debuging.
//#define RBHIRAASIC_DEBUG                         //
//#define RBHIRA_DEBUG_READORDER                   // Output HiRA readout order debugging.
//#define RBHIRA_DEBUG                             // Output HiRA related debugging.
//#define RBSCALER_DEBUG                           // Output Scaler related debugging
//#define RBS800_DEBUG

// Define the Experiment
#define EXPERIMENT_09084                         // Use code related to this experiment.


//NOTE JJM June 7 2016
//Most of this file is wrong. At this point I don't care, but if I ever actually use 
//anything here, I will need to recheck all these settings

// Define which member classes to build.
//#define HIRACLASS_FLAG
//#define HIRACSICLASS_FLAG
//#define RBS800CLASS_FLAG
//#define FOURPICLASS_FLAG
//#define MCPCLASS_FLAG
//#define EPICSCLASS_FLAG
//#define SCALERCLASS_FLAG

// Global Variable Definitions
#define RBMCP_NQDCS            1                   // Number of MCP QDC's
#define RBMCP0_NSTAGES         2                   // Number of MCP0 gain stages.
#define RBMCP1_NSTAGES         2                   // Number of MCP1 gain stages.

#define RBHIRA_MB_SLOTS        16                  // Number of MB slots.
#define RBHIRA_SI_CHANNELS     32                  // Number of strips for each side of a detector.
#define RBHIRA_CSI_CHANNELS    4                   // Number of CsI per telescope.
#define RBHIRA_MAX_TELE_LABEL  20                  // 
#define RBHIRA_NTELES          16                  // Number of telescopes used in the array.
#define RBHIRA_NMBS            4                   // Number of MB's used in the array.
#define RBHIRA_NTOWERS         4                   // Number of towers used for the array.
#define RBHIRA_MAXROW          4                   // Max row of a tower.
#define RBHIRA_MAXCOL          4                   // Max col of a tower.

#define RBSCALER_NSCALERS      64                  // Max number of scalers used.

// Define options
#define OP_GEN_NEW             0                     // Store calibrated trees in new file?
#define RBHIRA_OP_CDISABLE     1                     // Disable initial filling of calibrated branches.
#define RBHIRA_OP_DE           1                     // dE's installed?
#define RBHIRA_OP_E            1                     // E's installed?
#define RBHIRA_OP_CSI          1                     // CsI's installed?
#define RBHIRA_OP_USETIMES     0                     // Using HiRA times?

#define TS800_OP_TCRDC         0                     // Using tracking CRDC's?
#define TS800_OP_TPPAC         1                     // Using tracking PPAC'S?

// Telescope Mapping
// Define this static array with values starting with the bottom left detector
// proceeding up the tower.  Continue with bottom of next tower and so on.
static const int teleID[RBHIRA_NTELES] = {7,0,1,2,3,4,5,6,8,9,10,11,12,16,17,19};
// Telescope face tower mapping
// Format is COL 0=dE, COL 1=EF COL 2=EB.  Each ROW is a telescope in order of it's
// index number.
static const int kTowerMap[RBHIRA_NTELES][3] = {{-1,0,0},
					       {-1,0,0},
					       {-1,0,0},
					       {-1,0,0},
					       {-1,1,1},
					       {-1,1,1},
					       {-1,1,1},
					       {-1,1,1},
					       {-1,2,2},
					       {-1,2,2},
					       {-1,2,2},
					       {-1,2,2},
					       {-1,3,3},
					       {-1,3,3},
					       {-1,3,3},
					       {-1,3,3}};


// Tower Mapping
// This is a visual map of the telescopes.  If a space is blank fill set it to -1
static const int towerMatrix[RBHIRA_MAXROW][RBHIRA_MAXCOL] = {{ 2,  6, 11, 19},
							    { 1,  5, 10, 17},
							    { 0,  4,  9, 16},
							    { 7,  3,  8, 12}};

