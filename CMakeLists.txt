cmake_minimum_required(VERSION 3.10)

#set the project name
project(REngine)

include(CTest)
add_subdirectory(Tests)

set(CMAKE_BUILD_TYPE "Debug")

include_directories("${PROJECT_SOURCE_DIR}/CMake")
include_directories("${PROJECT_SOURCE_DIR}/source")
include_directories("${PROJECT_SOURCE_DIR}/Math")

include(${PROJECT_SOURCE_DIR}/Cmake/TargetArchDetect.cmake)
target_architecture(TARGET_ARCH)

include(${PROJECT_SOURCE_DIR}/Cmake/CrossGuidPlatformDependencies.cmake)

include(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

aux_source_directory(. DIR_SRCS)

add_subdirectory(source)
add_subdirectory(Math)

add_executable(REngine ${DIR_SRCS})

SET_TARGET_PROPERTIES(SOURCE PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(REngine SOURCE)

SET_TARGET_PROPERTIES(MATH PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(REngine MATH)