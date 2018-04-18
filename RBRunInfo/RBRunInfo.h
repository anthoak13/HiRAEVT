#ifndef RBRUNINFO_H
#define RBRUNINFO_H

#include <fstream>
#include <sstream>

#include <RBDAQStackInfo.h>
#include <RBHINPUnpacker.h>
#include <RBPh7xxUnpacker.h>
#include <RBCAEN7xxUnpacker.h>
#include <RBCAEN1x90Unpacker.h>
#include <RBSisTimestampUnpacker.h>

class RBRunInfo
{
public:
  RBRunInfo(int run_number, const char * run_title="");                             //! Constructor
  ~RBRunInfo();                                          //! Destructor

  int LoadDAQSettings(const char *);                     //! Read DAQ settings from file
  int LoadPedestals(const char *);                       //! Read Pedetal settings from file
  int LoadMapping(const char *);                         //! Read channel Mapping from file

  const char * GetTitle() const;                         //! Returns run title
  int GetRunNumber() const;                              //! Returns run number
  const char * GetEvtFilePath() const;                   //! Returns path containing evt files for the run
  int GetNStacks() const;                                //! Returns number of stacks
  RBDAQStackInfo * GetStackInfo(int) const;              //! Returns a RBDAQStackInfo object

  void SetEvtFilePath(const char *);                     //! Set path for evt files of the run
  void SetRunTitle(const char *);                        //! Set run title

  void AddModuleToStackInfo(RBElectronics *);            //! Add a module to the RBDAQStackInfo object

private:
  std::string fRunTitle;                                 //!
  int fRunNumber;                                        //!
  std::string fEvtFilePath;                              //!
  int fNStacks;
  bool fDAQLoaded;                                       //!
  bool fPedestalsLoaded;                                 //!
  bool fMappingLoaded;                                   //!

  std::vector <RBDAQStackInfo *> fStackInfo;             //!

  void ParseDefineDAQLine(const char *);
  void ParseAddDAQLine(const char *);

};

#endif
