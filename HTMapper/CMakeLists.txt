# Create an executable to unpack the data called HiRAEVTMapper


add_executable(HiRAEVTMapper.exe  MapperMain.cxx )

set(DEPENDENCIES
  ${ROOT_LIBRARIES}
  nlohmann_json::nlohmann_json
  
  HTLogo
 # HTExperimentalSetup
  HTRootElectronics
#  HTDetectors
  )


set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTMapper
  ${CMAKE_SOURCE_DIR}/HTLogo
  ${CMAKE_SOURCE_DIR}/HTRunInfo
  ${CMAKE_SOURCE_DIR}/HTExperimentalSetup
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
  ${CMAKE_SOURCE_DIR}/HTRawDataReader
  ${CMAKE_SOURCE_DIR}/HTElectronics

  ${CMAKE_SOURCE_DIR}/HTDetectors
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTDetector
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTForwardArray
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTHiRA
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTIonChamber
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTMcp
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTMicroball
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTNeutronWall
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTSisTimestamp
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTTDCSpare
  ${CMAKE_SOURCE_DIR}/HTDetectors/HTVetoWall

  )

target_link_libraries(HiRAEVTMapper.exe ${DEPENDENCIES} )
include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )


