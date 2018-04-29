#ifndef HTVETOWALL_H
#define HTVETOWALL_H

/* *******************************************************************************************************
 * HTVetoWall Class
 * v1.0 04/29/2018
 * class to store Veto Walls data
 * implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * data of the veto wall. The class is composed by:
 * 1 HTVetoWallArray
 *
 * class HTVetoWallArray : it is an array of HTVetoWallBar objects
 * each HTVetoWallBar object represents a vertical scintillator bar:
 *
 *        top (Short_t)
 *        time top (Double_t)
 *         _____
 *        |    |
 *        |    |
 *        |    |
 *        |    |
 *        |    |
 *        |    |
 *        |____|
 *
 *        bottom (Short_t)
 *        time bottom (Double_t)
 */

#include <TROOT.h>
#include <TTree.h>
#include <HTVetoWallRootEvent.h>
#include <HTVetoWallMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>

#include <HTVetoWallArray.h>

class HTVetoWall : public HTDetector
{
public :
  HTVetoWall(const char *, int);                   //!Constructor
  ~HTVetoWall();                                   //!Destructor

  void Clear() override;                           //!Clear. Not used in the current implementation

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTVetoWallArray * fVetoWall;                     //!HTVetoWallArray object containing event-by-event mapped data
  HTVetoWallRootEvent * fevt;                      //!RootEvent type of the detector

};

#endif
