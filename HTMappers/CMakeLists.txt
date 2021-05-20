# Create a library called libHTMappers

set(LIBRARY_NAME HTMappers)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

# When in doubt set a dependency to be public, that way it's headers will be passed along
set(DEPS_PRIVATE
  nlohmann_json::nlohmann_json
  )

set(DEPS_PUBLIC
  HTRootElectronics
  HTDetectors
  )

set(SRCS
  # Put source files to compile here
  HTDetectorMapper.cxx
  HTSimpleDetectorMapper.cxx
  HTMcpMapper.cxx
  HTMusicICMapper.cxx
  HTTimestampMapper.cxx

  HTMapperFactory.cxx
  HTMapper.cxx
  )

generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PRIVATE ${DEPS_PRIVATE}
  DEPS_PUBLIC ${DEPS_PUBLIC}
  )
