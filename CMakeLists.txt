cmake_minimum_required(VERSION 3.5)
project(SimpleRenderEngine CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#########################################################
# Variables
#########################################################
 
if(ARCH STREQUAL "x86")
    SET(PLATFORM_ARCH "x86")
else()
    SET(PLATFORM_ARCH "x64")
endif()
 
 
IF(WIN32)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/windows)
    SET(LIBRARY_EXTENSION "lib")
ELSEIF(APPLE)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/macos)
    SET(LIBRARY_EXTENSION "dylib")
ELSEIF(UNIX)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/linux)
    SET(LIBRARY_EXTENSION "so")
ENDIF()
 
SET(CROSS_PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/multi)


#########################################################
# FIND OPENGL
#########################################################
IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
ELSE (APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    IF(UNIX)
        find_package(GLEW REQUIRED)
    ELSE(UNIX)
        find_package(glew REQUIRED)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(sre)
include_directories(include)

option(USE_OPENVR "Enable OpenVR" ON)

set(OPENVR_LIB)
IF (USE_OPENVR)
	find_package(OpenVR REQUIRED)
	include_directories(${OPENVR_INCLUDE_DIR})
	IF(UNIX)
		add_definitions(-DSRE_OPENVR)
	ELSE(UNIX)	
		add_definitions(/DSRE_OPENVR)
	ENDIF(UNIX)
	
    set(OPENVR_LIB ${OPENVR_LIBRARY})
ENDIF(USE_OPENVR)


set(DLLFileList)
IF (WIN32)
    SET(SDL2_DLL_FOLDER "${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}")

    #set visual studio to MT
   foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)

 
    file(GLOB DLLFileList
        "${SDL2_DLL_FOLDER}/*.dll"
    )
 
    set(DLLFileList ${DLLFileList} "${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/openvr_api.dll")
 
ENDIF(WIN32)


add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)
add_subdirectory(utils)
