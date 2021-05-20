################################################################################
#    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#    Copyright (C) 2019 CERN and copyright holders of ALICE O2                 #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Creates a target for a new library, and adds everything needed to build it, including the dictionary
# All file paths shouls be relative ones to the calling CMakeLists.txt file
#
# Arguments to function:
#
# target: The name of the library to build (required)
# SRCS: Sources to build (required)
# LINKDEF: Name of the linkdef file (will skip dictionary generation of not present)
# HDRS: List of all header files to use in library generation.
#     - Will use all SRCS renamed from .cxx to .h if empty
# INCLUDE_DIR: List of include directories in addition to ROOT_INCLUDE_DIR
# LIBRARY_DIR: List of link directories in addition to ROOT_LIBRARY_DIR
# DEPS_PUBLIC: Public dependencies
# DEPS_PRIVATE: Private dependencies

function(generate_target_root_library target)
  cmake_parse_arguments(PARSE_ARGV
    1
    HT
    ""
    "LINKDEF"
    "SRCS;HDRS;INCLUDE_DIR;LIBRARY_DIR;DEPS_PUBLIC;DEPS_PRIVATE"
    )


  # Check for required and set defaults
  if(HT_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR "Unexpected unparsed arguments: ${HT_UNPARSED_ARGUMENTS}")
  endif()

  if(NOT HT_SRCS)
    message(FATAL_ERROR "Missing required argument: SRCS")
  endif()

  if(NOT HT_HDRS)
    CHANGE_FILE_EXTENSION(*.cxx *.h HT_HDRS "${SRCS}")
  endif()

  #Check that files are relative
  foreach(h ${HT_SRCS} ${HT_HDRS} ${HT_LINKDEF})
    if(IS_ABSOLUTE ${h})
      message(
        FATAL_ERROR "add_root_dictionary only accepts relative paths, but the"
        "following path is absolute : ${h}")
    endif()
  endforeach()

  # Create the target and add the dependencies
  add_library(${target} SHARED ${HT_SRCS})
  set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

  target_link_libraries(${target} PUBLIC ${HT_DEPS_PUBLIC})
  target_link_libraries(${target} PRIVATE ${HT_DEPS_PRIVATE})

  target_include_directories(${target} PUBLIC ${HT_INCLUDE_DIR} ${ROOT_INCLUDE_DIR})
  target_link_directories(${target} PUBLIC ${HT_LIBRARY_DIR} ${ROOT_LIBRARY_DIR})

  # Make the dictionary
  if(HT_LINKDEF)
    hiraevt_target_root_dictionary( ${target}
      HEADERS ${HT_HDRS}
      LINKDEF ${HT_LINKDEF})
  endif()
  
endfunction()

# based on the work in https://github.com/AliceO2Group/AliceO2

#
# hiraevt_target_root_dictionary generates one dictionary to be added to a target.
#
# Besides the dictionary source itself two files are also generated : a rootmap
# file and a pcm file. Those two will be installed alongside the target's
# library file
#
# arguments :
#
# * 1st parameter (required) is the target the dictionary should be added to
#
# * HEADERS (required) is a list of relative filepaths needed for the dictionary
#   definition
#
# * LINKDEF (required) is a single relative filepath to the LINKDEF file needed
#   by rootcling.
#
# LINKDEF and HEADERS must contain relative paths only (relative to the
# CMakeLists.txt that calls this add_root_dictionary function).
#
# The target must be of course defined _before_ calling this function (i.e.
# add_library(target ...) has been called).
#
# In addition :
#
# * target_include_directories _must_ have be called as well, in order to be
#   able to compute the list of include directories needed to _compile_ the
#   dictionary
#
# Note also that the generated dictionary is added to PRIVATE SOURCES list of
# the target.
#

function(hiraevt_target_root_dictionary target)
  cmake_parse_arguments(PARSE_ARGV
    1
    A
    ""
    "LINKDEF"
    "HEADERS;BASENAME")
  if(A_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR "Unexpected unparsed arguments: ${A_UNPARSED_ARGUMENTS}")
  endif()

  if(A_BASENAME)
    message(STATUS "BASENAME parameter is deprecated. Will be ignored")
  endif()

  set(required_args "LINKDEF;HEADERS")
  foreach(required_arg IN LISTS required_args)
    if(NOT A_${required_arg})
      message(FATAL_ERROR "Missing required argument: ${required_arg}")
    endif()
  endforeach()

  # check all given filepaths are relative ones
  foreach(h ${A_HEADERS} ${A_LINKDEF})
    if(IS_ABSOLUTE ${h})
      message(
        FATAL_ERROR "add_root_dictionary only accepts relative paths, but the"
        "following path is absolute : ${h}")
    endif()
  endforeach()

  # convert all relative paths to absolute ones. LINKDEF must be the last one.
  unset(headers)
  foreach(h ${A_HEADERS} ${A_LINKDEF})
    get_filename_component(habs ${CMAKE_CURRENT_SOURCE_DIR}/${h} ABSOLUTE)
    list(APPEND headers ${habs})
  endforeach()

  # check all given filepaths actually exist
  foreach(h ${headers})
    get_filename_component(f ${h} ABSOLUTE)
    if(NOT EXISTS ${f})
      message(
        FATAL_ERROR
        "add_root_dictionary was given an inexistant input include ${f}")
    endif()
  endforeach()

  # Generate the pcm and rootmap files alongside the library
  get_property(lib_output_dir
    TARGET ${target}
    PROPERTY LIBRARY_OUTPUT_DIRECTORY)

  set(lib_output_dir ${CMAKE_BINARY_DIR}/lib)


  # Define the names of generated files
  get_property(basename TARGET ${target} PROPERTY OUTPUT_NAME)
  if(NOT basename)
    set(basename ${target})
  endif()
  set(dictionary G__${basename})
  set(dictionaryFile ${CMAKE_CURRENT_BINARY_DIR}/${dictionary}.cxx)
  set(pcmBase ${dictionary}_rdict.pcm)
  set(pcmFile ${lib_output_dir}/${pcmBase})
  set(rootmapFile ${lib_output_dir}/lib${basename}.rootmap)

  # get the list of compile_definitions
  set(prop $<TARGET_PROPERTY:${target},COMPILE_DEFINITIONS>)

  # Build the LD_LIBRARY_PATH required to get rootcling running fine
  #
  # Need at least root core library
  # get_filename_component(LD_LIBRARY_PATH ROOT::Core DIRECTORY)
  set(LD_LIBRARY_PATH ${ROOT_LIBRARY_DIR})
  # and possibly toolchain libs if we are using a toolchain
  if(DEFINED ENV{GCC_TOOLCHAIN_ROOT})
    set(LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:$ENV{GCC_TOOLCHAIN_ROOT}/lib")
    set(LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:$ENV{GCC_TOOLCHAIN_ROOT}/lib64")
  endif()

  set(includeDirs $<TARGET_PROPERTY:${target},INCLUDE_DIRECTORIES>)

  file(GENERATE OUTPUT log CONTENT "${includeDirs}")
  
  # add a custom command to generate the dictionary using rootcling
  # cmake-format: off
  set(space " ")
  add_custom_command(
    OUTPUT ${dictionaryFile} ${pcmFile} ${rootmapFile}
    VERBATIM
    COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$ENV{LD_LIBRARY_PATH}"
    ${ROOT_CINT_EXECUTABLE}
    -f ${dictionaryFile}
    -inlineInputHeader
    -rmf ${rootmapFile}
    -rml $<TARGET_FILE_NAME:${target}>
    -I$<JOIN:${includeDirs},$<SEMICOLON>-I>
    $<$<BOOL:${prop}>:-D$<JOIN:${prop},$<SEMICOLON>-D>>
    ${headers}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${pcmBase} ${pcmFile}
    COMMAND_EXPAND_LISTS
    DEPENDS ${headers})
  # cmake-format: on

  # add dictionary source to the target sources
  target_sources(${target} PRIVATE ${dictionaryFile})

  get_property(libs TARGET ${target} PROPERTY INTERFACE_LINK_LIBRARIES)
  if(NOT RIO IN_LIST libs)
    # if(NOT ROOT::RIO IN_LIST libs)
    # add ROOT::IO if not already there as a target that has a Root dictionary
    # has to depend on ... Root
    target_link_libraries(${target} PUBLIC RIO)
    # target_link_libraries(${target} PUBLIC ROOT::RIO)
  endif()

  # Get the list of include directories that will be required to compile the
  # dictionary itself and add them as private include directories
  foreach(h IN LISTS A_HEADERS)
    if(IS_ABSOLUTE ${h})
      message(FATAL_ERROR "Path ${h} should be relative, not absolute")
    endif()
    get_filename_component(a ${h} ABSOLUTE)
    string(REPLACE "${h}" "" d "${a}")
    list(APPEND dirs ${d})
  endforeach()
  list(REMOVE_DUPLICATES dirs)
  target_include_directories(${target} PRIVATE ${dirs})

  # will install the rootmap and pcm files alongside the target's lib
  get_filename_component(dict ${dictionaryFile} NAME_WE)
  #message("Install dir: ${CMAKE_INSTALL_LIBDIR}")
  #gmessage("Install dir: ${CMAKE_INSTALL_INCLUDEDIR}")

  install(FILES ${rootmapFile} ${pcmFile} DESTINATION ${CMAKE_INSTALL_LIBDIR})

endfunction()


################################################################################
#
# Exchange file extention of LIST from FILE_EXT1 to FILE_EXT2
# and assign the newly created list to OUTVAR.
# The input list LIST is not changed at all
# Ex : CHANGE_FILE_EXTENSION(*.cxx *.h TRD_HEADERS "${TRD_SRCS}")
#
################################################################################
MACRO (CHANGE_FILE_EXTENSION FILE_EXT1 FILE_EXT2 OUTVAR LIST)
  SET(BLA)
  IF (${FILE_EXT1} MATCHES "^[*][.]+.*$")
    STRING(REGEX REPLACE "^[*]+([.].*)$" "\\1" FILE_EXT1_NEW ${FILE_EXT1})
  ENDIF  (${FILE_EXT1} MATCHES "^[*][.]+.*$")
  IF (${FILE_EXT2} MATCHES "^[*][.]+.*$")
    STRING(REGEX REPLACE "^[*]+([.].*)" "\\1" FILE_EXT2_NEW ${FILE_EXT2})
  ENDIF  (${FILE_EXT2} MATCHES "^[*][.]+.*$")
  foreach (_current_FILE ${LIST})
    STRING(REGEX REPLACE "^(.*)${FILE_EXT1_NEW}$" "\\1${FILE_EXT2_NEW}" test ${_current_FILE})
    SET (BLA ${BLA} ${test})
  endforeach (_current_FILE ${ARGN})
  SET (${OUTVAR} ${BLA})
ENDMACRO (CHANGE_FILE_EXTENSION)

################################################################################
# Make the given list have only one instance of each unique element and
# store it in var_name.
################################################################################

MACRO(UNIQUE var_name list)
  SET(unique_tmp "")
  FOREACH(l ${list})
    STRING(REGEX REPLACE "[+]" "\\\\+" l1 ${l})
    IF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
      SET(unique_tmp ${unique_tmp} ${l})
    ENDIF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
  ENDFOREACH(l)
  SET(${var_name} ${unique_tmp})
ENDMACRO(UNIQUE)

Macro(ROOT_GENERATE_DICTIONARY)

  # All Arguments needed for this new version of the macro are defined
  # in the parent scope, namely in the CMakeLists.txt of the submodule
  set(Int_LINKDEF ${LINKDEF})
  set(Int_DICTIONARY ${DICTIONARY})
  set(Int_LIB ${LIBRARY_NAME})

  set(Int_INC ${INCLUDE_DIRECTORIES} ${SYSTEM_INCLUDE_DIRECTORIES})
  set(Int_HDRS ${HDRS})
  set(Int_DEF ${DEFINITIONS})

  # Convert the values of the variable to a semi-colon separated list
  separate_arguments(Int_INC)
  separate_arguments(Int_HDRS)
  separate_arguments(Int_DEF)

  # Format neccesary arguments
  # Add -I and -D to include directories and definitions
  Format(Int_INC "${Int_INC}" "-I" "")
  Format(Int_DEF "${Int_DEF}" "-D" "")

  #---call rootcint / cling --------------------------------
  set(OUTPUT_FILES ${Int_DICTIONARY})

  If (CMAKE_SYSTEM_NAME MATCHES Linux)
    Set(MY_LD_LIBRARY_PATH ${ROOT_LIBRARY_DIR}:${_intel_lib_dirs}:$ENV{LD_LIBRARY_PATH})
  ElseIf(CMAKE_SYSTEM_NAME MATCHES Darwin)
    Set(MY_LD_LIBRARY_PATH ${ROOT_LIBRARY_DIR}:$ENV{DYLD_LIBRARY_PATH})
  EndIf()

  get_filename_component(script_name ${Int_DICTIONARY} NAME_WE)
  String(REPLACE ";" " " Int_DEF_STR "${Int_DEF}")
  String(REPLACE ";" " " Int_INC_STR "${Int_INC}")
  String(REPLACE ";" " " Int_HDRS_STR "${Int_HDRS}")

  Set(EXTRA_DICT_PARAMETERS "")
  Set(Int_ROOTMAPFILE ${LIBRARY_OUTPUT_PATH}/lib${Int_LIB}.rootmap)
  Set(Int_PCMFILE G__${Int_LIB}Dict_rdict.pcm)
  Set(OUTPUT_FILES ${OUTPUT_FILES} ${Int_PCMFILE} ${Int_ROOTMAPFILE})
  Set(EXTRA_DICT_PARAMETERS ${EXTRA_DICT_PARAMETERS}
    -rmf ${Int_ROOTMAPFILE}
    -rml ${Int_LIB}${CMAKE_SHARED_LIBRARY_SUFFIX})
  Set_Source_Files_Properties(${OUTPUT_FILES} PROPERTIES GENERATED TRUE)
  String(REPLACE ";" " " EXTRA_DICT_PARAMETERS_STR "${EXTRA_DICT_PARAMETERS}")
  


  # We need some environment variables which are present when running cmake at the
  # time we run make. To pass the variables a script is created containing the
  # correct values for the needed variables
  
  Configure_File(${PROJECT_SOURCE_DIR}/cmake/scripts/generate_dictionary_root.sh.in
    ${CMAKE_CURRENT_BINARY_DIR}/generate_dictionary_${script_name}.sh
    )
  
  
  
  
  Add_Custom_Command(OUTPUT  ${OUTPUT_FILES}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/generate_dictionary_${script_name}.sh
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${Int_PCMFILE} ${LIBRARY_OUTPUT_PATH}/${Int_PCMFILE}
    DEPENDS ${Int_HDRS} ${Int_LINKDEF}
    )
  Install(FILES ${LIBRARY_OUTPUT_PATH}/${Int_PCMFILE} ${Int_ROOTMAPFILE} DESTINATION lib)
  

EndMacro(ROOT_GENERATE_DICTIONARY)

# Based on FairRoot's generate library macro. Uses the following variables which are reset
# at the end of each call
#
# LIBRARY_NAME: The name of the library to build
# DICTIONARY: The name of the dictionary file to generate (defaults to "G_${LIBRARY_NAME}Dict.cxx")
# LINKDEF: Name of the linkdef file (will skip dictionary generation of not present)
# SRCS: Sources to build
# HEADERS: List of all header files. Will use all SRCS renamed from .cxx to .h if empty
# NO_DICT_SRCS: 
# DEPENDENCIES: 
#
#

Macro(GENERATE_LIBRARY)
  
  set(Int_LIB ${LIBRARY_NAME})

  # Set dictionary name
  Set(DictName "G__${Int_LIB}Dict.cxx")
  If(NOT DICTIONARY)
    Set(DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/${DictName})
  EndIf(NOT DICTIONARY)

  If( IS_ABSOLUTE ${DICTIONARY})
    Set(DICTIONARY ${DICTIONARY})
  Else( IS_ABSOLUTE ${DICTIONARY})
    Set(Int_DICTIONARY ${CMAKE_CURRENT_SOURCE_DIR}/${DICTIONARY})
  EndIf( IS_ABSOLUTE ${DICTIONARY})
  
  Set(Int_SRCS ${SRCS})

  If(HEADERS)
    Set(HDRS ${HEADERS})
  Else(HEADERS)
    CHANGE_FILE_EXTENSION(*.cxx *.h HDRS "${SRCS}")
  EndIf(HEADERS)

  # Install the headers into /include
  install(FILES ${HDRS} DESTINATION include)
  
  If(LINKDEF)
    If( IS_ABSOLUTE ${LINKDEF})
      Set(Int_LINKDEF ${LINKDEF})
    Else( IS_ABSOLUTE ${LINKDEF})
      Set(Int_LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/${LINKDEF})
    EndIf( IS_ABSOLUTE ${LINKDEF})
    
    ROOT_GENERATE_DICTIONARY()

    SET(Int_SRCS ${Int_SRCS} ${DICTIONARY})
    SET_SOURCE_FILES_PROPERTIES(${DICTIONARY}
      PROPERTIES COMPILE_FLAGS "-Wno-old-style-cast"
      )
  EndIf(LINKDEF)


  set(Int_DEPENDENCIES)
  foreach(d ${DEPENDENCIES})

    get_filename_component(_ext ${d} EXT)
    If(NOT _ext MATCHES a$)
      set(Int_DEPENDENCIES ${Int_DEPENDENCIES} ${d})
    Else()
      Message("Found Static library with extension ${_ext}")
      get_filename_component(_lib ${d} NAME_WE)
      set(Int_DEPENDENCIES ${Int_DEPENDENCIES} ${_lib})
    EndIf()
  endforeach()

  ############### build the library #####################

  #create the library target with the name Int_LIB 
  If(${CMAKE_GENERATOR} MATCHES Xcode)
    Add_Library(${Int_LIB} SHARED ${Int_SRCS} ${NO_DICT_SRCS} ${HDRS} ${LINKDEF})
  Else()
    Add_Library(${Int_LIB} SHARED ${Int_SRCS} ${NO_DICT_SRCS} ${LINKDEF})
  EndIf()

  # set target link libraries
  target_link_libraries(${Int_LIB} ${Int_DEPENDENCIES})

    set_target_properties(${Int_LIB} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

  ############### install the library ###################
  install(TARGETS ${Int_LIB} DESTINATION lib)

#  Set(LIBRARY_NAME)
#  Set(DICTIONARY)
#  Set(LINKDEF)
#  Set(SRCS)
#  Set(HEADERS)
#  Set(NO_DICT_SRCS)
#  Set(DEPENDENCIES)

  
EndMacro(GENERATE_LIBRARY)
