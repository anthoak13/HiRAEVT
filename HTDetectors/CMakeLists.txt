# Create a library for all detectors
# To add a detector, add the required source files in SRCS,
# and add the directory with the headers in INCLUDE_DIRECTORIES


set(LINKDEF HTDetectorsLinkDef.h)
set(LIBRARY_NAME HTDetectors)

set(DEPENDENCIES
  nlohmann_json::nlohmann_json
  )

set(SRCS
  # Put source files to compile here
  HTDetector.cxx
  HTSimpleDetector.cxx
  HTMcp.cxx
  
  HTCalibrator.cxx
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRootElectronics

  ${CMAKE_SOURCE_DIR}/HTDetectors
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()




