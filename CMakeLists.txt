cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CLIP_VERSION_MAJOR 0)
set(CLIP_VERSION_MINOR 1)
set(CLIP_VERSION ${CLIP_VERSION_MAJOR}.${CLIP_VERSION_MINOR})
project(clip VERSION ${CLIP_VERSION} LANGUAGES CXX)
message(STATUS "clip -- Building version: ${CLIP_VERSION}")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(CLIP_HEADER_ONLY "Use header-only or compiled library" OFF)
if(${CLIP_HEADER_ONLY})
	message(STATUS "clip -- Using header-only version of clip")
	add_library(clip_header_only INTERFACE)
	add_library(clip::clip_header_only ALIAS clip_header_only)
	target_include_directories(clip_header_only INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/single_header">
		"$<INSTALL_INTERFACE:CMAKE_INSTALL_INCLUDEDIR>")
endif()

option(CLIP_BUILD_SHARED "Build shared or static library" OFF)
if(NOT ${CLIP_HEADER_ONLY})
	message(STATUS "clip -- Using compiled version of clip")
	set(SOURCES src/CommandLineParser.cpp)
	set(HEADERS 
		include/CommandLineInputParser/clip.hpp
		include/CommandLineInputParser/CommandLineParser.hpp
		include/CommandLineInputParser/OptionalArgument.hpp
		include/CommandLineInputParser/ArgumentValue.hpp
		src/Match.hpp
	)
	if(${CLIP_BUILD_SHARED})
		add_library(clip SHARED ${SOURCES} ${HEADERS})
	else()
		add_library(clip STATIC ${SOURCES} ${HEADERS})
	endif()
	add_library(clip::clip ALIAS clip)
	target_include_directories(clip PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
	set_target_properties(clip PROPERTIES VERSION ${CLIP_VERSION} SOVERSION ${CLIP_VERSION_MAJOR})
	#set_target_properties(clip PROPERTIES DEBUG_POSTFIX d)
endif()

option(CLIP_BUILD_EXAMPLES "Build library examples" ON)
if(${CLIP_BUILD_EXAMPLES})
    message(STATUS "clip -- Building examples")
    add_subdirectory(examples)
endif()

option(CLIP_BUILD_TESTS "Build library tests" OFF)
if(${CLIP_BUILD_TESTS})
    message(STATUS "clip -- Building tests")
    add_subdirectory(tests)
endif()

option(CLIP_INSTALL "Install library" ON)
if(${CLIP_INSTALL})
	install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    if(${CLIP_HEADER_ONLY})
		install(TARGETS clip_header_only EXPORT clip DESTINATION "${CMAKE_INSTALL_LIBDIR}")
    else()
		install(TARGETS clip EXPORT clip DESTINATION "${CMAKE_INSTALL_LIBDIR}")
	endif()
endif()