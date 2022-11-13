cmake_minimum_required(VERSION 3.0.0)
project(comp-grafica VERSION 0.1.0)

include(CTest)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SDL2 REQUIRED)

add_executable(comp-grafica 

src/utils.cpp
src/matrix.cpp
src/scene.cpp
src/lightSource.cpp
src/ambient.cpp
src/directional.cpp
src/point.cpp
src/spot.cpp
src/object.cpp
src/sphere.cpp
src/plane.cpp
src/cylinder.cpp
src/cone.cpp
src/mesh.cpp
src/main.cpp)

target_link_libraries(comp-grafica ${SDL2_LIBRARIES})
#target_link_libraries(comp-grafica SDL2::SDL2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)