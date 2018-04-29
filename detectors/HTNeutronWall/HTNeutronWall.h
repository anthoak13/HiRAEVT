#ifndef HTNEUTRONWALL_H
#define HTNEUTRONWALL_H

/* *******************************************************************************************************
 * HTNeutronWall Class
 * v1.0 04/29/2018
 * class to store Neutron Walls data is derived from RBNeutronWall class
 * implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * 12/01/2017 v1.0beta Simple version containing only the raw
 * data of the neutron wall. The class is composed by:
 * 1 HTNeutronWallArray
 *
 *
 * class HTNeutronWallArray : it is an array of HTNeutronWallBar objects
 *                          ____________________________________________
 *                         |                                           |
 *                         |             scintillator bar              |
 *                         |___________________________________________|
 *                          ____________________________________________
 * anode common (left)     |                                           | anode common (right)
 * anode individual (left) |             scintillator bar              | anode individual (right)
 * time (left)             |___________________________________________| time (right)
 *                          ____________________________________________
 *                         |                                           |
 *                         |             scintillator bar              |
 *                         |___________________________________________|
 *
 */

#include <TROOT.h>
#include <TTree.h>
#include <HTNeutronWallRootEvent.h>
#include <HTNeutronWallMap.h>
#include <HTRootCAEN7xx.h>
#include <HTRootCAEN1x90.h>
#include <HTDetector.h>
#include <HTNeutronWallArray.h>

class HTNeutronWall : public HTDetector
{
public :
  HTNeutronWall(const char *, int);                //!Constructor
  ~HTNeutronWall();                                //!Destructor

  void Clear() override;                           //!Clear to -9999

  void InitTTreeBranch(TTree *) override;          //!Initialize TTree Branch containing detector ROOT type
  void BuildEvent() override;                      //!Calls individual electronic modules to feel detector branches
  void FillMappedData() override;                  //!Stores mapped data in detector ROOT class to be written on the output tree

private :
  HTNeutronWallArray *fNeutronWall;                //!HTNeutronWallArray containing mapped event-by-event data
  HTNeutronWallRootEvent * fevt;                   //!RootEvent type of the detector

};

#endif
