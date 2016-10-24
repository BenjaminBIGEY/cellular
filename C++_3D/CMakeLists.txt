cmake_minimum_required(VERSION 3.6)
project(C___3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp World/Display.cpp World/Display.h World/Ant.cpp World/Ant.h World/Unit.cpp World/Unit.h World/World.cpp World/World.h World/Grid3D.cpp World/Grid3D.h)
add_executable(C___3D ${SOURCE_FILES})