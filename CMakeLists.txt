cmake_minimum_required(VERSION 3.22)
project(crimson_like)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(IMGUI_DIR "imgui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(glbinding REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

file(GLOB SOURCES 
	"${SOURCE_DIR}/*.cpp"
	"${IMGUI_DIR}/*.cpp"
	)

file(GLOB_RECURSE HEADERS 
	"${INCLUDE_DIR}/*.h" 
	"${IMGUI_DIR}/*.h" 
	)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} glbinding::glbinding glbinding::glbinding-aux) 

enable_testing()

add_subdirectory(UT)
add_subdirectory(googletest)
