# Create a library called libHTMappers

set(LINKDEF GenLinkDef.h)
set(LIBRARY_NAME HTMappers)
set(DEPENDENCIES
  ${ROOT_LIBRARIES}
  nlohmann_json::nlohmann_json
  
  HTRootElectronics
  HTDetectors
  )

set(SRCS
  # Put source files to compile here
  HTDetectorMapper.cxx
  HTSimpleDetectorMapper.cxx
  HTMcpMapper.cxx
  HTMusicICMapper.cxx
  HTMapperFactory.cxx
  
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTMappers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  ${CMAKE_SOURCE_DIR}/HTDetectors
  ${CMAKE_SOURCE_DIR}/mapper
  
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )

GENERATE_LIBRARY()


