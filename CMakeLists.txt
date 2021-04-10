cmake_minimum_required(VERSION 3.11)

# Set the project name
project(HiRAEVT)
set(HiRAEVT_MAJOR_VERSION 0)
set(HiRAEVT_MINOR_VERSION 0)
set(HiRAEVT_PATCH_VERSION 0)
set(HiRAEVT_VERSION "${HiRAEVT_MAJOR_VERSION}.${HiRAEVT_MINOR_VERSION}.${HiRAEVT_PATCH_VERSION}")
  
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# For now needs to be built against FairRoot. On fishtank, fairroot is built agains root 6.12, and that is not
# exposed as a module to load excpet through FairRoot.
if(NOT DEFINED ENV{FAIRROOTPATH})
  message( FATAL_ERROR "Enviroment variable FAIRROOTPATH was not defined, this is needed to properly link against AT-TPC")
endif(NOT DEFINED ENV{FAIRROOTPATH})

# Set variables so we can find FairRoot
set(FAIRROOTPATH $ENV{FAIRROOTPATH})
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(FairRoot)

# Load macros
include(FairMacros)
include(WriteConfigFile)

set(FAIRROOT_LIBRARY_PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES}
  VERSION "${HiRAEVT_VERSION}"
  SOVERSION "${HiRAEVT_MAJOR_VERSION}"
  )

# I think everything after this point should be FairRoot independent except for the macros I'm using
# but those should be addable later 

# Set compile flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -std=c++14)

# Set output location and location of JSON library
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# Force out of source build and UNIX system
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
if(insource)
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME} should be built as an out of source build. Please create a extra build directory and run the command 'cmake path_to_source_dir' in this newly created directory. You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.")
endif(insource)

if(NOT UNIX)
  message(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
endif(NOT UNIX)

find_package(ROOT 6.12 REQUIRED)

##### FairRoot specific #####

SetBasicVariables()
Generate_Version_Info()

#### End FairRoot specific #####


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

# Walk through the project and compile libraries and executables
add_subdirectory(HTElectronics)
add_subdirectory(HTDetectors)
add_subdirectory(HTLogo)
add_subdirectory(HTExperimentalSetup)
add_subdirectory(HTExperiment)
add_subdirectory(HTRawDataReader)
add_subdirectory(HTRootElectronics)
add_subdirectory(HTRunInfo)

# build executables
add_subdirectory(FilterUnpacker)
add_subdirectory(HTMapper)
add_subdirectory(jsonTest)

WRITE_CONFIG_FILE(config.sh)
