/* *******************************************************************************************************
 * HTNeutronWallBar Class
 * v1.0 04/29/2018
 * simple Neutron Wall scintillator bar derived from HTNeutronWallBar class
 * implemented by Daniele Dell'Aquila (dellaqui@nscl.msu.edu)
 * 12/04/2017 v1.0 : simple version containing anode and dinode (time)
 * signals raw data for right and left ends of a scintillator bar.
 *
 *                          ____________________________________________
 * anode common (left)     |                                           | anode common (right)
 * anode individual (left) |             scintillator bar              | anode individual (right)
 * time (left)             |___________________________________________| time (right)
 *
 * ********************************************************************************************************/

#ifndef HTNEUTRONWALLBAR_H
#define HTNEUTRONWALLBAR_H

#include <TROOT.h>

class HTNeutronWallBar
{
private:
  // rawdata
  Short_t  fAnoodeCommLeft;
  Short_t  fAnodeIndLeft;
  Double_t fTimeLeft;
  Short_t  fAnoodeCommRight;
  Short_t  fAnodeIndRight;
  Double_t fTimeRight;

public:
  HTNeutronWallBar ();                  //constructor
  virtual ~HTNeutronWallBar();          //destructor

  //Setting methods
  void SetAnodeCommonLeft(Short_t);
  void SetAnodeIndividualLeft(Short_t);
  void SetTimeLeft(Double_t);
  void SetAnodeCommonRight(Short_t);
  void SetAnodeIndividualRight(Short_t);
  void SetTimeRight(Double_t);

  //Getting methods
  Short_t  GetAnodeCommonLeft() const; //Anode common signal left (channels)
  Short_t  GetAnodeIndividualLeft() const; //Anode individual signal left (channels)
  Double_t GetTimeLeft() const; //Time signal left (channels)
  Short_t  GetAnodeCommonRight() const; //Anode common signal right (channels)
  Short_t  GetAnodeIndividualRight() const; //Anode individual signal right (channels)
  Double_t GetTimeRight() const; //Time signal right (channels)

  //Getting methods pointers
  Short_t  * GetAnodeCommonLeftPointer(); //Anode common signal left (channels)
  Short_t  * GetAnodeIndividualLeftPointer() ; //Anode individual signal left (channels)
  Double_t * GetTimeLeftPointer() ; //Time signal left (channels)
  Short_t  * GetAnodeCommonRightPointer() ; //Anode common signal right (channels)
  Short_t  * GetAnodeIndividualRightPointer() ; //Anode individual signal right (channels)
  Double_t * GetTimeRightPointer() ; //Time signal right (channels)

  void Clear();
} ;

#endif
