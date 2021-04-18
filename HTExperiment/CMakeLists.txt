# Create a library called libHTElectronics

set(LINKDEF GenLinkDef.h)
set(LIBRARY_NAME HTExperiment)

set(DEPENDENCIES
  HTRootElectronics
  )

set(SRCS
  # Put source files to compile here

  HTExperiment.cxx
  HTExperimentInfo.cxx
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTExperiment
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/FilterUnpacker
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}

  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


