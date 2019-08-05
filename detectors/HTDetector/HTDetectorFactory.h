/* Singelton factory for creating detectors
 *
 * Adam Anthony 7/25/2019
 *
 */
#ifndef HTDETECTORFACTORY_H
#define HTDETECTORFACTORY_H

#include <string>

#include "HTDetector.h"

#include "HTTDCSpare.h"
#include "HTHiRA.h"
#include "HTNeutronWall.h"
#include "HTVetoWall.h"
#include "HTForwardArray.h"
#include "HTMicroball.h"
#include "HTSisTimestampe15190.h"
#include "HTIonChamber.h"
#include "HTMCP.h"

class HTDetectorFactory
{
public:
  
  static HTDetectorFactory* Instance();

  HTDetector* CreateDetector(const std::string& detType,
			     const std::string& detName,
			     const int numDets);
  
protected:
  HTDetectorFactory();
  ~HTDetectorFactory();

private:
  static HTDetectorFactory *_instance;
};


#endif /** end ifndef HTDETECTORFACTORY_H **/
