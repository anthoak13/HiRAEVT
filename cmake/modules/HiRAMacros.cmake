#Based on FairRoot stuff

macro(CHECK_BUILD)
  # Checks to make sure it makes sense to run
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
  if(insource)
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME} should be built as an out of source build. Please create a extra build directory and run the command 'cmake path_to_source_dir' in this newly created directory. You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.")
  endif(insource)

  if(NOT UNIX)
    message(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
  endif(NOT UNIX)

   String(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}" _same)
   If(_same)
      MESSAGE(FATAL_ERROR "Your build and installation directory is the same one. This option does not work. Please change either your build or your installation directory and rerun cmake.")
   EndIf(_same)
endmacro()
