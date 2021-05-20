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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ROOT_INCLUDE_DIR}
  ${json_INCLUDE_DIR}
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}

  )

GENERATE_LIBRARY()

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(${LIBRARY_NAME} PUBLIC ${LINK_DIRECTORIES})

