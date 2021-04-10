//
//  HTElectronicsLinkDef.h
//
//
//  Created by Andrew Rogers on 3/20/15.
//
//

#ifndef _HTElectronicsLinkDef_h
#define _HTElectronicsLinkDef_h

#pragma link off all globals;
#pragma link off all classes;

#pragma link C++ class HTTimestamp + ;
#pragma link C++ class HTHINPUnpacker + ;
#pragma link C++ class HTHINPHit + ;
#pragma link C++ class HTCAEN7xxUnpacker + ;
#pragma link C++ class HTCAEN1x90Unpacker + ;
#pragma link C++ class HTMADC32Unpacker + ;
#pragma link C++ class HTPh7xxUnpacker + ;
#pragma link C++ class HTUSBStack + ;
#pragma link C++ class HTUSBStackMarker + ;
#pragma link C++ class HTElectronics + ;
#pragma link C++ class HTSisTimestampUnpacker + ;

#endif
