# Create an executable to unpack the data called HiRAEVTMapper

set(execName HiRAEVTMapper.exe)
add_executable(${execName}  MapperMain.cxx)

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

target_link_libraries(${execName} ${DEPENDENCIES} )
target_link_directories(${execName} PRIVATE ${LINK_DIRECTORIES} )
target_include_directories(${execName} PRIVATE ${INCLUDE_DIRECTORIES} )
install(TARGETS ${execName}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
