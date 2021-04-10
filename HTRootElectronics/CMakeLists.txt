# Create a library called libHTElectronics

set(LINKDEF "")
set(LIBRARY_NAME HTRootElectronics)

set(DEPENDENCIES
  HTElectronics
  )

set(SRCS
  # Put source files to compile here

  HTRootElectronics.cxx
  HTRootCAEN1x90.cxx
  HTRootCAEN7xx.cxx
  HTRootHINP.cxx
  HTRootMADC32.cxx
  HTRootSisTimestamp.cxx
  HTRootTimestamp.cxx 
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  ${CMAKE_SOURCE_DIR}/HTElectronics

  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}

  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


