#ifndef HTMCP_H
#define HTMCP_H

/* *******************************************************************************************************
 * HTMcp Class
 * v1.0 0 8/5/2019
 * class to store mcp data
 * implemented by Adam Anthony (anthonya@nscl.msu.edu)
 *
 * - HTMcp
 * | - fMulti
 * | - fEAnode[fMulti]
 * | - fEBack[fMulti]
 * | - fTimeAnode[fMulti]
 * | - fTimeBack[fMulti]
 */

#include <HTDetector.h>
#include <HTMcpMap.h>
#include <HTMcpRootEvent.h>
#include <HTRootCAEN1x90.h>
#include <HTRootCAEN7xx.h>
#include <TROOT.h>
#include <TTree.h>

class HTMcp : public HTDetector {
public:
   HTMcp(const char *, int); //! Constructor
   ~HTMcp();                 //! Destructor

   void Clear() override; //! Clear. Not used in the current implementation.

   void InitTTreeBranch(TTree *) override; //! Initialize TTree Branch containing detector ROOT type
   void BuildEvent() override;             //! Calls individual electronic modules to feel detector branches
   void FillMappedData() override; //! Stores mapped data in detector ROOT class to be written on the output tree

private:
   HTMcpRootEvent *fevt; //! RootEvent type of the detector

   void InitMapping() override;
};

#endif /* #ifndef HTMCP_H */
