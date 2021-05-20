cmake_minimum_required(VERSION 3.11)



# Set the project name and version
set(HiRAEVT_MAJOR_VERSION 2)
set(HiRAEVT_MINOR_VERSION 0)
set(HiRAEVT_PATCH_VERSION 0)
set(HiRAEVT_VERSION "${HiRAEVT_MAJOR_VERSION}.${HiRAEVT_MINOR_VERSION}.${HiRAEVT_PATCH_VERSION}")
project(HiRAEVT VERSION ${HiRAEVT_VERSION})  

# Checks to make sure it makes sense to run
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
if(insource)
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME} should be built as an out of source build. Please create a extra build directory and run the command 'cmake path_to_source_dir' in this newly created directory. You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.")
endif(insource)

if(NOT UNIX)
  message(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
endif(NOT UNIX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set variables so we can find FairRoot if needed
set(FAIRROOTPATH $ENV{FAIRROOTPATH})
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules" ${CMAKE_MODULE_PATH})




# Set compile flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS -std=c++14)

# Set output location of objects and libraries
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
Set(LD_LIBRARY_PATH  ${LIBRARY_OUTPUT_PATH} ${LD_LIBRARY_PATH})
Set(PATH ${EXECUTABLE_OUTPUT_PATH} ${PATH})


# Set project version
set(PROJECT_LIBRARY_PROPERTIES ${HIRAEVT_LIBRARY_PROPERTIES}
  VERSION "${HiRAEVT_VERSION}"
  SOVERSION "${HiRAEVT_MAJOR_VERSION}"
  )

# Version is the minimum version of root to load
find_package(FairRoot)
find_package(ROOT 6.12 REQUIRED)

include(${CMAKE_SOURCE_DIR}/cmake/modules/ROOTMacros.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/WriteConfigFile.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/modules/TargetRootDictionary.cmake)
include(GNUInstallDirs)

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

#gadd_subdirectory(jsonTest)

# Walk through the project and compile libraries and executables
# Libraries just for unpacker
add_subdirectory(HTUnpackers)
add_subdirectory(HTExperiment)

# Libraries shared by unpacker and mapper
add_subdirectory(HTRootElectronics)

# Libraries used by just mapper
add_subdirectory(HTDetectors)
add_subdirectory(HTMappers)


# build executables
add_subdirectory(unpacker)
add_subdirectory(mapper)


WRITE_CONFIG_FILE(config.sh)
