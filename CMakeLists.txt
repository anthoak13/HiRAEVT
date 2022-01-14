cmake_minimum_required(VERSION 3.11)

# Set the project name and version
set(HiRAEVT_MAJOR_VERSION 2)
set(HiRAEVT_MINOR_VERSION 0)
set(HiRAEVT_PATCH_VERSION 0)
set(HiRAEVT_VERSION "${HiRAEVT_MAJOR_VERSION}.${HiRAEVT_MINOR_VERSION}.${HiRAEVT_PATCH_VERSION}")

# Set project version and other global library properties
project(HiRAEVT VERSION ${HiRAEVT_VERSION})  
set(PROJECT_LIBRARY_PROPERTIES ${HIRAEVT_LIBRARY_PROPERTIES}
  VERSION "${HiRAEVT_VERSION}"
  SOVERSION "${HiRAEVT_MAJOR_VERSION}"
  )

# Install path is changed to "install" if not given a value by the user
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "..." FORCE)
  message("Setting default install prefix to: ${CMAKE_INSTALL_PREFIX}")
endif()

if(NOT DEFINED BUILD_UNPACKERS)
  set(BULD_UNPACKERS ON)
  message("Building unpackers by default. Disable with -DBUILD_UNPACKERS=OFF")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set variables so we can find root, fairroot, and nscldaq
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
if(EXISTS $ENV{FAIRROOTPATH})
  list(APPEND CMAKE_MODULE_PATH "$ENV{FAIRROOTPATH}/share/fairbase/cmake/modules")
endif()
message("Looking for modules in: ${CMAKE_MODULE_PATH}")

# Set compile flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -std=c++14)

# Version is the minimum version of root to load
find_package(ROOT 6.16 REQUIRED CONFIG)

## Include macros and functions ##
include(HiRAMacros)
include(ROOTMacros)
include(GNUInstallDirs)

Find_Program(ROOT_CINT_EXECUTABLE
  NAMES rootcint
  PATHS ${ROOT_BINARY_DIR}
  NO_DEFAULT_PATH
  )


#Sanity check on builds that would error out
CHECK_BUILD()


# Fetch the json library for use
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)


FetchContent_GetProperties(json)

if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)

  #Hack around so the json library is properly exported with HiRAEVT
  set_target_properties(nlohmann_json PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "")
  target_include_directories(nlohmann_json
    INTERFACE
    $<BUILD_INTERFACE:${json_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

  install(DIRECTORY ${json_SOURCE_DIR}/include/nlohmann DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(TARGETS nlohmann_json EXPORT GeneratedRootLibTargets)
endif()


### List all subdirectories to build ###

#Libraries
if(BUILD_UNPACKERS)
  add_subdirectory(HTUnpackers)
  add_subdirectory(unpacker)
endif()

add_subdirectory(HTExperiment)
add_subdirectory(HTRootElectronics)
add_subdirectory(HTDetectors)
add_subdirectory(HTMappers)


# build executables

add_subdirectory(mapper)
#add_subdirectory(jsonTest)

# Add install targets for libraries
install(EXPORT GeneratedRootLibTargets
  FILE HiRAEVT.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/HiRAEVT/cmake )

# Create the find module thing
include(CMakePackageConfigHelpers)

#generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/HiRAEVTConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/HiRAEVT/cmake
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

# Generate the version file for the config
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/HiRAEVTConfigVersion.cmake"
  VERSION ${HiRAEVT_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

# install the configuration file
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/HiRAEVTConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/HiRAEVTConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/HiRAEVT/cmake
  )

