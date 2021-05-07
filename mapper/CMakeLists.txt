# Create an executable to unpack the data called HiRAEVTMapper


add_executable(HiRAEVTMapper.exe  MapperMain.cxx HTMapper.cxx)

set(DEPENDENCIES
  ${ROOT_LIBRARIES}
  nlohmann_json::nlohmann_json
  
 HTRootElectronics
 HTMappers
 HTDetectors
 )


set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTMappers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  ${CMAKE_SOURCE_DIR}/HTDetectors

  )

target_link_libraries(HiRAEVTMapper.exe ${DEPENDENCIES} )
include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )


