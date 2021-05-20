# Create a library called libHTElectronics

set(LIBRARY_NAME HTExperiment)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

set(DEPS_PUBLIC
  HTRootElectronics
  )

set(SRCS
  # Put source files to compile here

  HTExperiment.cxx
  HTExperimentInfo.cxx
  )


generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PUBLIC ${DEPS_PUBLIC}
  )


