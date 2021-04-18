# Create a library called libHTElectronics

set(LINKDEF "")
set(LIBRARY_NAME HTRunInfo)

set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here

  HTRunInfo.cxx
  HTDAQStackInfo.cxx
  HTModuleInfo.cxx
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTRunInfo
  ${CMAKE_SOURCE_DIR}/HTElectronics

  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}

  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


