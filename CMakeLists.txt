cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(PandemicRoom)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package( Threads )

include_directories(${SDL2_INCLUDE_DIRS} src)
file(GLOB SOURCES "src/*.cpp")

add_executable(PandemicRoom ${SOURCES})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(PandemicRoom ${SDL2_LIBRARIES})
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
