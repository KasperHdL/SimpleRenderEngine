cmake_minimum_required(VERSION 3.5)
project(SimpleRenderEngine CXX)

list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)
    


#########################################################
# Local Config
#########################################################
include("${CMAKE_SOURCE_DIR}/cmake/local_config.cmake" OPTIONAL RESULT_VARIABLE LOCAL_CONFIG_RESULT_VAR)
if(LOCAL_CONFIG_RESULT_VAR STREQUAL NOTFOUND)

    file(COPY "${CMAKE_SOURCE_DIR}/cmake/templates/local_config_template.cmake" DESTINATION "${CMAKE_SOURCE_DIR}")
    file(RENAME "${CMAKE_SOURCE_DIR}/local_config_template.cmake" "${CMAKE_SOURCE_DIR}/cmake/local_config.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/local_config.cmake")
endif()

#########################################################
# Variables
#########################################################
 
if(ARCH STREQUAL "x86")
    SET(PLATFORM_ARCH "x86")
else()
    SET(PLATFORM_ARCH "x64")
endif()
 
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

IF(WIN32)
    SET(PLATFORM_PATHS ${CMAKE_SOURCE_DIR}/libraries/windows)
    SET(LIBRARY_EXTENSION "lib")
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
		add_definitions(-DSRE_OPENVR)
	
    set(OPENVR_LIB ${OPENVR_LIBRARY})
    list(APPEND EXTRA_LIBS ${OPENVR_LIBRARY})
ENDIF(USE_OPENVR)

add_definitions(-DSRE_EXPORT)

set(DLLFileList)
IF (WIN32)
    SET(SDL2_DLL_FOLDER "${PLATFORM_PATHS}/SDL2/lib/${PLATFORM_ARCH}")

    list(APPEND CMAKE_CXX_FLAGS_RELEASE "/MD")
    list(APPEND CMAKE_CXX_FLAGS_DEBUG "/MDd")
 
    file(GLOB DLLFileList
        "${SDL2_DLL_FOLDER}/*.dll"
    )
 
    set(DLLFileList ${DLLFileList} "${PLATFORM_PATHS}/openvr/x86/openvr_api.dll")
 
ENDIF(WIN32)


add_subdirectory(src)
#add_subdirectory(examples)
#add_subdirectory(test)
#add_subdirectory(utils)
