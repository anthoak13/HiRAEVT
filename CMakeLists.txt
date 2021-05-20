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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Set variables so we can find root and fairroot
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_MODULE_PATH "$ENV{FAIRROOTPATH}/share/fairbase/cmake/modules")
message("Prefix: ${CMAKE_MODULE_PATH}")

# Set compile flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -std=c++14)

# Version is the minimum version of root to load
find_package(FairRoot)
find_package(ROOT 6.12 REQUIRED)

include(HiRAMacros)
include(ROOTMacros)
include(GNUInstallDirs)

#Sanity check on builds that would error out
CHECK_BUILD()

# Install path is changed to "install" if not given a value by the user
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "..." FORCE)
  message("Setting default install prefix to: ${CMAKE_INSTALL_PREFIX}")
endif()

# Fetch the json library
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


### List all subdirectories to build ###

#Libraries
add_subdirectory(HTUnpackers)
add_subdirectory(HTExperiment)
add_subdirectory(HTRootElectronics)
add_subdirectory(HTDetectors)
add_subdirectory(HTMappers)

# build executables
add_subdirectory(unpacker)
add_subdirectory(mapper)
#add_subdirectory(jsonTest)

#WRITE_CONFIG_FILE(config.sh)

