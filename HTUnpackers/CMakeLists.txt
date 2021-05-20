# Create a library called libHTUnapckers

set(LIBRARY_NAME HTUnpackers)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

set(DEPS_PUBLIC
  HTRootElectronics
  )
set(DEPS_PRIVATE
  nlohmann_json::nlohmann_json
  )

set(SRCS
  # Put source files to compile here
  HTModuleUnpacker.cxx  
  HTCAEN1x90Unpacker.cxx
  HTCAEN7xxUnpacker.cxx
  HTMADC32Unpacker.cxx
  HTSisTimestampUnpacker.cxx

  HTUnpackerFactory.cxx
  )

generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PUBLIC ${DEPS_PUBLIC}
  DEPS_PRIVATE ${DEPS_PRIVATE}
  )

#GENERATE_LIBRARY()


