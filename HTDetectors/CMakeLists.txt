# Create a library for all detectors
# To add a detector, add the required source files in SRCS,
# and add the directory with the headers in INCLUDE_DIRECTORIES

set(LIBRARY_NAME HTDetectors)
set(LINKDEF "${LIBRARY_NAME}LinkDef.h")

#Private dependencies (things that the caller will never need to access)
set(DEPS_PRIVATE
  nlohmann_json::nlohmann_json
  )

set(SRCS
  # Put source files to compile here
  HTDetector.cxx
  HTSimpleDetector.cxx
  HTMcp.cxx
  HTMusicIC.cxx
  HTTimestamp.cxx

  HTCalibrator.cxx
  )

# Create target for the library
generate_target_root_library( ${LIBRARY_NAME}
  SRCS ${SRCS}
  LINKDEF ${LINKDEF}
  DEPS_PRIVATE ${DEPS_PRIVATE}
  )





