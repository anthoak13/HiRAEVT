# Create a library called libHTUnapckers

set(LINKDEF GenLinkDef.h)
set(LIBRARY_NAME HTUnpackers)

set(DEPENDENCIES
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
set(HEADERS
  # Put source files to compile here
  HTModuleUnpacker.h
  HTCAEN1x90Unpacker.h
  HTCAEN7xxUnpacker.h
  HTMADC32Unpacker.h
  HTSisTimestampUnpacker.h

  HTUnpackerFactory.h
  )

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${json_INCLUDE_DIR}
  
  # Directories with headers
  ${CMAKE_SOURCE_DIR}/HTUnpackers
  ${CMAKE_SOURCE_DIR}/HTRootElectronics
    
  )

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  )

add_library(${LIBRARY_NAME} SHARED ${SRCS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

target_link_libraries(${LIBRARY_NAME} PUBLIC ${DEPENDENCIES})
target_link_libraries(${LIBRARY_NAME} PRIVATE ${DEPS_PRIVATE})
target_link_directories(${LIBRARY_NAME} PUBLIC ${LINK_DIRECTORIES})
set_target_properties(${LIBRARY_NAME} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

hiraevt_target_root_dictionary( ${LIBRARY_NAME}
  HEADERS ${HEADERS}
  LINKDEF ${LINKDEF})

#GENERATE_LIBRARY()


