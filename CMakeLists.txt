    #cmake -G "Eclipse CDT4 - Unix Makefiles" ..
    #SET (CMAKE_CXX_COMPILER "/usr/bin/g++")
    #Alternatively, you could configure a script for executing the program which then dynamically adjusts PATH (Windows), 
    #LD_LIBRARY_PATH (Linux) or DYLD_LIBRARY_PATH (Mac) before executing your binary. 
    #These environment variables are used to resolve shared libraries at runtime
    
    IF (${APPLE})
        MESSAGE(STATUS "WELCOME TO APPLE")
    
        set(CMAKE_MACOSX_RPATH ON)
        set(CMAKE_SKIP_BUILD_RPATH FALSE)
        set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
        set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
        set(CMAKE_INSTALL_NAME_DIR "@rpath")
        set(CMAKE_INSTALL_RPATH "@executable_path/..${CMAKE_INSTALL_PREFIX}/lib/shared")
    
    ENDIF()
    
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
    PROJECT(ChimericSequenceMaker)
    
    SET (ChimericSequenceMaker_VERSION_MAJOR 1)
    SET (ChimericSequenceMaker_VERSION_MINOR 0)
    
    #used by makefile users in order to install software at non-default location
    #make DESTDIR=/home/john install --> prepended with the DESTDIR value
    SET(CMAKE_INSTALL_PREFIX install)
    
    #SET(CMAKE_SKIP_BUILD_RPATH true )
    #Can manually add the sources using the set command as follows:
    FILE(GLOB SOURCES_MAIN "src/main/*.cpp")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/main")
    

    #Generate the static library from the sources
    FILE(GLOB SOURCES_STATIC "src/static/*.cpp")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/static")
    ADD_LIBRARY(calculSum STATIC "${SOURCES_STATIC}")
    INSTALL(TARGETS calculSum DESTINATION "lib/static")
    
    #Generate the shared library from the sources
    FILE(GLOB SOURCES_SHARED "src/shared/*.cpp")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/shared")
    ADD_LIBRARY(calculMean SHARED "${SOURCES_SHARED}")
    #MACOSX_RPATH is now specified for the following targets calcuMean
    #SET_TARGET_PROPERTIES(calculMean PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/shared")
    INSTALL(TARGETS calculMean DESTINATION "lib/shared")
    #MACOSX_RPATH is not specified for the following targets calcuMean
    
   # "Link a target to given libraries."
   find_package (Boost REQUIRED COMPONENTS system filesystem)
   if (Boost_FOUND)
        MESSAGE( STATUS "Boost_LIBRARIES FOUND         "  )   
        include_directories("${Boost_INCLUDE_DIRS}")
   endif ()
    
    #SET_TARGET_PROPERTIES(calculMean PROPERTIES LINKER_LANGUAGE CXX)
    #SET_TARGET_PROPERTIES(calculSum PROPERTIES LINKER_LANGUAGE CXX)
    
    #Build a stand alone program
    ADD_EXECUTABLE(ChimericSequenceMaker "${SOURCES_MAIN}")# "${SOURCES_STATIC}" "${SOURCES_SHARED}"
    
    TARGET_LINK_LIBRARIES(ChimericSequenceMaker calculMean) 
    TARGET_LINK_LIBRARIES(ChimericSequenceMaker calculSum)
    
     # Alternatively you could use ${Boost_LIBRARIES} here.
    TARGET_LINK_LIBRARIES(ChimericSequenceMaker "${Boost_LIBRARIES}")

    MESSAGE( STATUS "Boost_LIBRARIES:         " ${Boost_LIBRARIES} )
    
    INSTALL(TARGETS ChimericSequenceMaker DESTINATION bin)
   
    ADD_CUSTOM_COMMAND(TARGET calculMean
                       POST_BUILD
                       COMMAND "${CMAKE_SOURCE_DIR}/bash/post-build.sh" "HELLO YOU!"
                       WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       COMMENT "Post-build is Running" VERBATIM
    )
   
    #SET_TARGET_PROPERTIES(ChimericGenomeMaker PROPERTIES LINKER_LANGUAGE CXX)


   # If you want to share your lib and give description of the methods you need to make install & export header
    #INSTALL(FILES "${PROJECT_SOURCE_DIR}/include/static/calc_sum.h" DESTINATION include)
        
    
    # ------------------------- Begin Generic CMake Variable Logging ------------------
    
    
    MESSAGE( STATUS "CMAKE_INSTALL_NAME_DIR:         " ${CMAKE_INSTALL_NAME_DIR} )
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH:         " ${CMAKE_INSTALL_RPATH} )
    MESSAGE( STATUS "LINKER_LANGUAGE:         " ${LINKER_LANGUAGE} )
    
    # if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise 
    # this is the top level directory of your build tree 
    MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )
    
    # if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this 
    # is the directory where the compiled or generated files from the current CMakeLists.txt will go to 
    MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )
    
    # this is the directory, from which cmake was started, i.e. the top level source directory 
    MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )
    
    # this is the directory where the currently processed CMakeLists.txt is located in 
    MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )
    
    # contains the full path to the top level directory of your build tree 
    MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )
    
    # contains the full path to the root of your project source directory,
    # i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command 
    MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )
    
    # set this variable to specify a common place where CMake should put all executable files
    # (instead of CMAKE_CURRENT_BINARY_DIR)
    MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )
    
    # set this variable to specify a common place where CMake should put all libraries 
    # (instead of CMAKE_CURRENT_BINARY_DIR)
    MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )
    
    # tell CMake to search first in directories listed in CMAKE_MODULE_PATH
    # when you use FIND_PACKAGE() or INCLUDE()
    MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )
    
    # this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake) 
    MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
    
    # this is the CMake installation directory 
    MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )
    
    # this is the filename including the complete path of the file where this variable is used. 
    MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )
    
    # this is linenumber where the variable is used
    MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )
    
    # this is used when searching for include files e.g. using the FIND_PATH() command.
    MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )
    
    # this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
    MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )
    
    # the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1" 
    MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )
    
    # the short system name, e.g. "Linux", "FreeBSD" or "Windows"
    MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )
    
    # only the version part of CMAKE_SYSTEM 
    MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )
    
    # the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz") 
    MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )
    
    # is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
    MESSAGE( STATUS "UNIX: " ${UNIX} )
    
    # is TRUE on Windows, including CygWin 
    MESSAGE( STATUS "WIN32: " ${WIN32} )
    
    # is TRUE on Apple OS X
    MESSAGE( STATUS "APPLE: " ${APPLE} )
    
    # is TRUE when using the MinGW compiler in Windows
    MESSAGE( STATUS "MINGW: " ${MINGW} )
    
    # is TRUE on Windows when using the CygWin version of cmake
    MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )
    
    # is TRUE on Windows when using a Borland compiler 
    MESSAGE( STATUS "BORLAND: " ${BORLAND} )
    
    # Microsoft compiler 
    MESSAGE( STATUS "MSVC: " ${MSVC} )
    MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
    MESSAGE( STATUS "MSVC60: " ${MSVC60} )
    MESSAGE( STATUS "MSVC70: " ${MSVC70} )
    MESSAGE( STATUS "MSVC71: " ${MSVC71} )
    MESSAGE( STATUS "MSVC80: " ${MSVC80} )
    MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )
    
    # set this to true if you don't want to rebuild the object files if the rules have changed, 
    # but not the actual source files or headers (e.g. if you changed the some compiler switches) 
    MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )
    
    # since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing. 
    # If you don't like this, set this one to true.
    MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )
    
    # If set, runtime paths are not added when using shared libraries. Default it is set to OFF
    MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )
    
    # set this to true if you are using makefiles and want to see the full compile and link 
    # commands instead of only the shortened ones 
    MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )
    
    # this will cause CMake to not put in the rules that re-run CMake. This might be useful if 
    # you want to use the generated build files on another machine. 
    MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )
    
    # A simple way to get switches to the compiler is to use ADD_DEFINITIONS(). 
    # But there are also two variables exactly for this purpose: 
    
    # the compiler flags for compiling C sources 
    MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )
    
    # the compiler flags for compiling C++ sources 
    MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
    
    # Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug) 
    MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )
    
    # if this is set to ON, then all libraries are built as shared libraries by default.
    MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )
    
    # the compiler used for C files 
    MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
    
    # the compiler used for C++ files 
    MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )
    
    # if the compiler is a variant of gcc, this should be set to 1 
    MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )
    
    # if the compiler is a variant of g++, this should be set to 1 
    MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )
    
    # the tools for creating libraries 
    MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
    MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )
    
    # ENVIRONNEMENT VARIABLE 
    MESSAGE(STATUS "PATH : $ENV{PATH}")
    
    
    # ------------------------- End of Generic CMake Variable Logging ------------------