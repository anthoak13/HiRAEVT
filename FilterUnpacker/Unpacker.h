#ifndef UNPACKER_H
#define UNPACKER_H

#include "FragmentIndex.h"
#include "HTExperiment.h"

#include <TTree.h>
#include <ctime>
#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>

class Unpacker
{
  private:
    int      nevent;
    uint64_t fReadWords;            //
    float    fPercentDone;          // Percent done.
    time_t   fStart;                // Start conversion time.
    time_t   fNow;                  // Current time.
    double   fTimeElapsed;          // Time elapsed from fStart to fNow
    uint64_t m_lastTimestamp;

    uint64_t  fTimestampMismatch;
    bool      fFoundTimestampMismatch;

    char fSourceFileName[1000];
    bool fDebug;
    bool fMergedData;
//    double fDataFormatVersion;

    HTExperiment *fExperiment;

 public:
    Unpacker();
    Unpacker(const Unpacker& rhs);
    ~Unpacker();

    void Clear();

    void operator() (uint64_t eventTimestamp, uint32_t sourceId,
                     uint32_t barrierType,    std::string typeName,
                     uint32_t runNumber,      uint32_t timeOffset,
                     time_t   timestamp,      std::string  title);

    void operator() (FragmentIndex& index,
                     uint32_t totalSize, uint64_t eventTimestamp);
    void operator() (uint16_t *pBody, uint32_t totalSize);
    void operator() (uint16_t *pBody,
 		                 uint32_t totalSize, uint64_t eventTimestamp);

    static  unsigned long getLong(std::vector<unsigned short>& event, unsigned int offset);

    void InitializeUnpacker(char* sourceName);
    void SetDebug(bool flag){fDebug=flag;}

    bool IsDataMerged(){return fMergedData;}

    void PrintSummary();                 //! Print a general unpacking summary to standard output
    void AddTTreeUserInfo(TTree *);      //! Add User Info to TTree
    void EndUnpacking();                 //! Called at the end of the Unpacking process

  private:
    void PrintPercentage() const;        //! Display progress with residual time
    void PrintPercentageSimple() const;  //! Simple display progress
};

#endif
