cmake_minimum_required(VERSION 3.22)
project(crimson_like)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})

enable_testing()

add_subdirectory(UT)
add_subdirectory(googletest)
