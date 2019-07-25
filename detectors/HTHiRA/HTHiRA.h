#ifndef HTHIRA_H
#define HTHIRA_H

/* *******************************************************************************************************
 * HTHiRACsIArray Class
 * v1.0 04/30/2018
 * class to store HiRA CsI data
 * implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * Differently from the other detector cases, only HiRACsI are mapped with the same
 * logic: i.e. looping on each individual detector and retrieve the information from the
 * associated modules and then write down the information on the HiRAData class.
 * For the case of strip detectors, I rather loop directly on the module and fill
 * HiRAData strip objects with only the strips present in the RBHINPHit class
 *
 * - HTHiRACsIArray
 * | - int fNumCsI
 * | HTHiRACsI fCsI
 *
 * - HTHiRACsI
 * | - fEenergy
 * | - fTime
 */

#include <TROOT.h>
#include <TTree.h>

#include "../../electronics/RBHINPHit.h"

#include <HTHiRARootEvent.h>
#include <HTHiRAMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTRootHINP.h>
#include <HTDetector.h>
#include <TTreeReaderValue.h>

#include <HTHiRACsIArray.h>

class HTHiRA : public HTDetector
{
public :
  HTHiRA(const char *, int);                       //!Constructor
  ~HTHiRA();                                       //!Destructor

  void Clear() override;                           //!Clear to -9999

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTHiRACsIArray *fHiRACsI;                        //!HTHiRACsIArray containing CsI data mapped
  HTHiRARootEvent * fevt;                          //!RootEvent type of the detector

  void InitMapping() override;
};

#endif
