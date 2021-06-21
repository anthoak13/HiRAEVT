# Create a library called libHTElectronics

set(LIBRARY_NAME HTRootElectronics)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

set(DEPS
  ROOT::Core
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

# Create target for the library
generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PUBLIC ${DEPS}
  )

