# Create an executable to unpack the data called HiRAEVTUnpacker


add_executable(HiRAEVTUnpacker.exe FragmentIndex.cxx HTFilter.cxx SkeletonMain.cxx HTUnpacker.cxx)

set(DEPENDENCIES
  ${ROOT_LIBRARIES}
  nlohmann_json::nlohmann_json
  
  # nscldaq libraries required
  /usr/opt/nscldaq/current/lib/libException.so
  /usr/opt/nscldaq/current/lib/libdaqshm.so
  /usr/opt/nscldaq/current/lib/libdataformat.so	
  /usr/opt/nscldaq/current/lib/liburl.so	
  /usr/opt/nscldaq/current/lib/libfilter.so	

  HTUnpackers
  HTExperiment
  HTRootElectronics
  )

set(LINK_DIRECTORIES
  ${LINK_DIRECTORIES}

  /usr/opt/nscldaq/current/lib
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_SOURCE_DIR}/include
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTExperiment
  ${CMAKE_SOURCE_DIR}/HTUnpackers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics

  ${CMAKE_SOURCE_DIR}/unpacker

  /usr/opt/nscldaq/current/filterkit/include
  /usr/opt/nscldaq/current/include
  
  )

target_link_libraries(HiRAEVTUnpacker.exe ${DEPENDENCIES} )
include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )


