# Create a library called libHTElectronics

set(LINKDEF "")
set(LIBRARY_NAME HTLogo)

set(DEPENDENCIES

  )

set(SRCS
  # Put source files to compile here
  HiRAEVTLogo.cxx
  )

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/HTLogo

  )

set(LINK_DIRECTORIES

  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


