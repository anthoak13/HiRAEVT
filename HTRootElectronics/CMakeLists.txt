# Create a library called libHTElectronics

set(LINKDEF "GenLinkDef.h")
set(LIBRARY_NAME HTRootElectronics)

set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here

  HTRootModule.cxx
  HTRootCAEN1x90.cxx
  HTRootCAEN1x90SingleHit.cxx
  HTRootSisTimestamp.cxx
  HTRootAdc.cxx 
  HTRootModuleFactory.cxx
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
 
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}

  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


