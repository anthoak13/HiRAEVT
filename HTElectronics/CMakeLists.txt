# Create a library called libHTElectronics

set(LINKDEF GenLinkDef.h)
set(LIBRARY_NAME HTElectronics)
set(DEPENDENCIES
  HTRootElectronics
  )

set(SRCS
  # Put source files to compile here
  HTModuleUnpacker.cxx  
  HTCAEN1x90Unpacker.cxx
  HTCAEN7xxUnpacker.cxx
  HTMADC32Unpacker.cxx
  HTSisTimestampUnpacker.cxx
  HTUSBStack.cxx

  HTUnpackerFactory.cxx
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
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


