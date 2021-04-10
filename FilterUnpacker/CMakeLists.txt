# Create an executable to unpack the data called HiRAEVTUnpacker


add_executable(HiRAEVTUnpacker.exe Unpacker.cpp FragmentIndex.cpp CUnpackerFilter.cpp SkeletonMain.cpp)

set(DEPENDENCIES
  ${ROOT_LIBRARIES}

  # nscldaq libraries required
  /usr/opt/nscldaq/current/lib/libException.so
  /usr/opt/nscldaq/current/lib/libdaqshm.so
  /usr/opt/nscldaq/current/lib/libdataformat.so	
  /usr/opt/nscldaq/current/lib/liburl.so	
  /usr/opt/nscldaq/current/lib/libfilter.so	

  
  HTElectronics
  HTExperiment
  HTLogo
  HTRunInfo
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

  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTExperiment
  ${CMAKE_SOURCE_DIR}/HTElectronics
  ${CMAKE_SOURCE_DIR}/HTRunInfo
  ${CMAKE_SOURCE_DIR}/FilterUnpacker
  ${CMAKE_SOURCE_DIR}/HTLogo
  /usr/opt/nscldaq/current/filterkit/include
  /usr/opt/nscldaq/current/include
  
  )

target_link_libraries(HiRAEVTUnpacker.exe ${DEPENDENCIES} )
include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES} )


