cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(clip_examples LANGUAGES CXX)

function(link_clip EXAMPLE_TARGET)
	if(${HEADER_ONLY_LIBRARY})
		target_link_libraries(${EXAMPLE_TARGET} PRIVATE clip::clip_header_only)
		#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/single_header)	
	else()
		target_link_libraries(${EXAMPLE_TARGET} PRIVATE clip::clip)
		#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
	endif()
endfunction()

if(NOT TARGET clip)
	find_package(clip REQUIRED)
endif()

set(TARGET_NAME PositionalOptionalArgs)
add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE clip::clip)
#target_include_directories(${TARGET_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
#link_clip(${TARGET_NAME} ${HEADER_ONLY_LIBRARY})

