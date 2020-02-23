cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(clip_tests LANGUAGES CXX)

include(DownloadGoogleTest)
include(GoogleTest)

add_executable(${PROJECT_NAME}
	clip_tests.cpp
	Test_ArgumentValue.cpp
	Test_OptionalArgument.cpp
)

if(${CLIP_HEADER_ONLY})
	target_link_libraries(${PROJECT_NAME} 
		PRIVATE clip::clip_header_only 
		PUBLIC gtest gmock
	)
else()
	target_link_libraries(${PROJECT_NAME}
		PRIVATE clip::clip
		PUBLIC gtest gmock
	)
endif()

gtest_discover_tests(${PROJECT_NAME})

#[[

RUN CONAN (conanfile.txt)

# Declare test executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PUBLIC
	PRIVATE
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME} 
	PRIVATE ../src
	PRIVATE ../include)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

]]