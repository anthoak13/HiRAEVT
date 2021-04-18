# Create a library called libHTElectronics

set(LINKDEF HTExperimentalSetupLinkDef.h)
set(LIBRARY_NAME HTExperimentalSetup)
set(DEPENDENCIES
  nlohmann_json::nlohmann_json
  HTDetectors
  HTRunInfo
  )

set(SRCS
  # Put source files to compile here
  HTExperimentalSetup.cxx
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTExperimentalSetup
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRunInfo
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTDetector
  
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


