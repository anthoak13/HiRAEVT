#ifndef HTRUNINFO_H
#define HTRUNINFO_H

#include <fstream>
#include <sstream>

#include <HTDAQStackInfo.h>
#include <RBHINPUnpacker.h>
#include <RBPh7xxUnpacker.h>
#include <RBCAEN7xxUnpacker.h>
#include <RBCAEN1x90Unpacker.h>
#include <RBMADC32Unpacker.h>
#include <RBSisTimestampUnpacker.h>
#include <RBTimestamp.h>

class HTRunInfo
{
public:
  HTRunInfo(int run_number, const char * run_title="");                             //! Constructor
  ~HTRunInfo();                                          //! Destructor

  int LoadDAQSettings(const char *);                     //! Read DAQ settings from file
  int SetPedestalsFile(const char *);                    //! Set Pathname of pedestal file
  int SetMappingFile(const char *);                      //! Set Pathname of mapping file
  int SetCalibrationFile(const char *);                  //! Set Pathname of calibration file

  
  const char * GetTitle() const;                         //! Returns run title
  int GetRunNumber() const;                              //! Returns run number

  //! Returns path containing evt files for the run
  const char * GetEvtFilePath() const;                
  
  //! Returns the path to pedestal file for the run
  const char * GetPedestalFile() const;               

  //! Returns the path to the mapping file for the run
  const char * GetMappingFile() const;                   

  // Return the calibration file for the run
  const char* GetCalibrationFile() const;
  
  
  int GetNStacks() const;                                //! Returns number of stacks
  HTDAQStackInfo * GetStackInfo(int) const;              //! Returns a HTDAQStackInfo object

  void SetEvtFilePath(const char *);                     //! Set path for evt files of the run
  void SetRunTitle(const char *);                        //! Set run title

  void AddModuleToStackInfo(RBElectronics *);            //! Add a module to the HTDAQStackInfo object

private:
  std::string fRunTitle;                                 //!
  int fRunNumber;                                        //!
  std::string fEvtFilePath;                              //!
  std::string fPedestalsFilePath;                        //!
  std::string fMappingFilePath;                          //!
  std::string fCalibrationFilePath;
  int fNStacks;                                          //!
  bool fDAQLoaded;                                       //!
  bool fPedestalsFileSet;                                //!
  bool fMappingFileSet;                                  //!
  bool fCalibrationFileSet;
  std::vector <HTDAQStackInfo *> fStackInfo;             //!

  void ParseDefineDAQLine(const char *);
  void ParseAddDAQLine(const char *);

};

#endif
