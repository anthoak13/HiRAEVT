# Create a library called libHTElectronics

set(LIBRARY_NAME HTExperimentalSetup)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

set(DEPS_PUBLIC
  HTDetectors
  )
set(DEPS_PRIVATE
  nlohmann_json::nlohmann_json
  )

set(SRCS
  # Put source files to compile here
  HTExperimentalSetup.cxx
  )


generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PUBLIC ${DEPS_PUBLIC}
  )


