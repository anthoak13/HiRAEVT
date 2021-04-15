# Create a library called libHTElectronics

set(LINKDEF HTElectronicsLinkDef.h)
set(LIBRARY_NAME HTElectronics)
set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here
  HTModuleUnpacker.cxx  
  HTCAEN1x90Unpacker.cxx
  HTCAEN7xxUnpacker.cxx
  HTMADC32Unpacker.cxx
  HTSisTimestampUnpacker.cxx
  HTUSBStack.cxx
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
    
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


