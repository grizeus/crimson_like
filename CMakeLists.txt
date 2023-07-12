cmake_minimum_required(VERSION 3.22)
project(crimson_like)

set(SOURCE_DIR "src")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# find_package(SDL2_image REQUIRED)
# include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
#
# find_package(SDL2_ttf REQUIRED)
# include_directories(${SDL2_TTF_INCLUDE_DIRS})

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}) 
target_link_libraries(${PROJECT_NAME}_lib ${SDL2_LIBRARIES}) 

enable_testing()

add_subdirectory(UT)
add_subdirectory(googletest)
