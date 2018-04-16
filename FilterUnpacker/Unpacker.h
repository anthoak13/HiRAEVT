
#ifndef UNPACKER_H
#define UNPACKER_H

#include <ctime>
#include <stdint.h>
#include <string>
#include <string.h>


#ifndef __STL_VECTOR
#include <vector>
#ifndef __STL_VECTOR
#define __STL_VECTOR
#endif
#endif


class FragmentIndex;

// External class that defines the particular experimental setup.
//extern class RBSetup gSetup;

class RBSetup;
class RBExperiment;

class Unpacker
{
  private:
    int      nevent;
    uint64_t fCounter;              // Event counter.
    uint64_t fReadWords;            //
    float    fPercentDone;          // Percent done.
    time_t   fStart;                // Start conversion time.
    time_t   fNow;                  // Current time.
    uint64_t m_lastTimestamp;

    uint64_t  fTimestampMismatch;
    bool      fFoundTimestampMismatch;

    char fSourceFileName[1000];
    bool fDebug;
    bool fMergedData;
//    double fDataFormatVersion;

    RBSetup      *fSetup;

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

  private:
};

#endif
