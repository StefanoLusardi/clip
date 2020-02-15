cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(clip_examples LANGUAGES CXX)

function(add_clip_example EXAMPLE_TARGET)
	add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
	if(${CLIP_HEADER_ONLY})
		target_link_libraries(${EXAMPLE_TARGET} PRIVATE clip::clip_header_only)
	else()
		target_link_libraries(${EXAMPLE_TARGET} PRIVATE clip::clip)
	endif()
endfunction()

add_clip_example(PositionalOptionalArgs)


