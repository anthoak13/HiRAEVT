# Create a library for all detectors
# To add a detector, add the required source files in SRCS,
# and add the directory with the headers in INCLUDE_DIRECTORIES

set(LINKDEF HTDetectorsLinkDef.h)
set(LIBRARY_NAME HTDetectors)
set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here
  HTDetector/HTDetector.cxx
  HTDetector/HTDetectorFactory.cxx
  HTDetector/HTDetectorMap.cxx

  HTIonChamber/HTIonChamber.cxx
  HTIonChamber/HTIonChamberMap.cxx
  HTIonChamber/HTIonChamberRootEvent.cxx

  HTForwardArray/HTForwardArray.cxx
  HTForwardArray/HTForwardArrayCluster.cxx
  HTForwardArray/HTForwardArrayDetector.cxx
  HTForwardArray/HTForwardArrayMap.cxx
  HTForwardArray/HTForwardArrayRootEvent.cxx 

  HTHiRA/HTHiRA.cxx
  HTHiRA/HiRAConstants.cxx
  HTHiRA/HTHiRACsI.cxx
  HTHiRA/HTHiRACsIArray.cxx
  HTHiRA/HTHiRAMap.cxx
  HTHiRA/HTHiRARootEvent.cxx

  HTMcp/HTMcp.cxx
  HTMcp/HTMcpMap.cxx
  HTMcp/HTMcpRootEvent.cxx

  HTMicroball/HTMicroball.cxx
  HTMicroball/HTMicroballArray.cxx
  HTMicroball/HTMicroballDetector.cxx
  HTMicroball/HTMicroballMap.cxx
  HTMicroball/HTMicroballRing.cxx
  HTMicroball/HTMicroballRootEvent.cxx
  HTMicroball/MicroballConstants.cxx

  HTNeutronWall/HTNeutronWall.cxx
  HTNeutronWall/HTNeutronWallArray.cxx
  HTNeutronWall/HTNeutronWallBar.cxx
  HTNeutronWall/HTNeutronWallMap.cxx
  HTNeutronWall/HTNeutronWallRootEvent.cxx

  HTSisTimestamp/HTSisTimestamp.cxx
  HTSisTimestamp/HTSisTimestampMap.cxx
  HTSisTimestamp/HTSisTimestampRootEvent.cxx

  HTTDCSpare/HTTDCSpare.cxx
  HTTDCSpare/HTTDCSpareChannel.cxx
  HTTDCSpare/HTTDCSpareMap.cxx
    
  HTVetoWall/HTVetoWall.cxx
  HTVetoWall/HTVetoWallArray.cxx
  HTVetoWall/HTVetoWallBar.cxx
  HTVetoWall/HTVetoWallMap.cxx
  HTVetoWall/HTVetoWallRootEvent.cxx
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  ${CMAKE_SOURCE_DIR}/shared

  ${CMAKE_SOURCE_DIR}/HTDetectors
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTDetector
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTForwardArray
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTHiRA
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTIonChamber
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTMcp
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTMicroball
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTNeutronWall
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTSisTimestamp
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTTDCSpare
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTVetoWall
  
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()




