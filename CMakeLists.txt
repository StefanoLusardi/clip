cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(CommandLineInputParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(HEADER_ONLY_LIBRARY "Use header-only version of the library" ON)
if(${HEADER_ONLY_LIBRARY})
	add_library(${PROJECT_NAME} INTERFACE)
	target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:"${PROJECT_SOURCE_DIR}/single_header/">
		$<INSTALL_INTERFACE:include>)
endif()

option(BUILD_LIBRARY "Use compiled version of the library" OFF)
if(${BUILD_LIBRARY})
	add_library(${PROJECT_NAME} STATIC)
	target_sources(${PROJECT_NAME}
		PUBLIC
			include/CommandLineInputParser/clip.hpp
			include/CommandLineInputParser/CommandLineParser.hpp
			include/CommandLineInputParser/OptionalArgument.hpp
			include/CommandLineInputParser/ArgumentValue.hpp
		PRIVATE
			src/CommandLineParser.cpp
			src/Match.hpp
	)
endif()

option(BUILD_EXAMPLES "Build library examples" ON)
if(${BUILD_EXAMPLES})
    message(STATUS "Building examples")
    add_subdirectory(examples)
endif()