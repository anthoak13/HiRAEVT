#ifndef HTMCP_H
#define HTMCP_H

/* *******************************************************************************************************
 * HTMCP Class
 * v1.0 0 8/5/2019
 * class to store mcp data 
 * implemented by Adam Anthony (anthonya@nscl.msu.edu)
 *
 * - HTMCP
 * | - fMulti
 * | - fEAnode[fMulti]
 * | - fEBack[fMulti]
 * | - fTimeAnode[fMulti]
 * | - fTimeBack[fMulti]
 */

#include <TROOT.h>
#include <TTree.h>
#include <HTMCPRootEvent.h>
#include <HTMCPMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>


class HTMCP : public HTDetector
{
public :
  HTMCP(const char *, int);               //!Constructor
  ~HTMCP();                               //!Destructor

  void Clear() override;                           //!Clear. Not used in the current implementation.

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTMCPRootEvent * fevt;                  //!RootEvent type of the detector

  void InitMapping() override;
};

#endif /* #ifndef HTMCP_H */
