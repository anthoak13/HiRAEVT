# Create a library for all detectors
# To add a detector, add the required source files in SRCS,
# and add the directory with the headers in INCLUDE_DIRECTORIES

message("Running CMake~~~~")

set(LINKDEF HTDetectorsLinkDef.h)
set(LIBRARY_NAME HTDetectors)

set(DEPENDENCIES
  nlohmann_json::nlohmann_json
  )

set(SRCS
  # Put source files to compile here
  HTDetector/HTDetector.cxx
  HTDetector/HTDetectorFactory.cxx
  HTDetector/HTDetectorMap.cxx

#  HTIonChamber/HTIonChamber.cxx
#  HTIonChamber/HTIonChamberMap.cxx
#  HTIonChamber/HTIonChamberRootEvent.cxx

#  HTMcp/HTMcp.cxx
#  HTMcp/HTMcpMap.cxx
#  HTMcp/HTMcpRootEvent.cxx

#  HTSisTimestamp/HTSisTimestamp.cxx
#  HTSisTimestamp/HTSisTimestampMap.cxx
#  HTSisTimestamp/HTSisTimestampRootEvent.cxx
    
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRootElectronics

  ${CMAKE_SOURCE_DIR}/HTDetectors
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTDetector
#  ${CMAKE_SOURCE_DIR}/HTDetectors/HTIonChamber
#  ${CMAKE_SOURCE_DIR}/HTDetectors/HTMcp
#  ${CMAKE_SOURCE_DIR}/HTDetectors/HTSisTimestamp
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()




