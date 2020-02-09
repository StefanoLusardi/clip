cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIP CommandLineInputParser)

#set(EXAMPLE_TARGET ArgumentValue)
#add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
#target_link_libraries(${EXAMPLE_TARGET} PRIVATE CLP)
#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	

#set(EXAMPLE_TARGET EnvironmentVars)
#add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
#target_link_libraries(${EXAMPLE_TARGET} PRIVATE CLP)
#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
#
#set(EXAMPLE_TARGET OptionalArgs)
#add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
#target_link_libraries(${EXAMPLE_TARGET} PRIVATE CLP)
#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
#
#set(EXAMPLE_TARGET PositionalArgs)
#add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
#target_link_libraries(${EXAMPLE_TARGET} PRIVATE CLP)
#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
#
set(EXAMPLE_TARGET PositionalOptionalArgs)
add_executable(${EXAMPLE_TARGET} ${EXAMPLE_TARGET}.cpp)
target_link_libraries(${EXAMPLE_TARGET} PRIVATE ${CLP})
target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/single_header)	
#target_include_directories(${EXAMPLE_TARGET} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)	
