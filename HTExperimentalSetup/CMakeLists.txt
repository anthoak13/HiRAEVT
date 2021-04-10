# Create a library called libHTElectronics

set(LINKDEF HTExperimentalSetupLinkDef.h)
set(LIBRARY_NAME HTExperimentalSetup)
set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here
  HTExperimentalSetup.cxx
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTExperimentalSetup
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRunInfo
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  
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


