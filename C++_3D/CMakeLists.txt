cmake_minimum_required(VERSION 3.6)
project(langton3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{SFML_ROOT}/cmake/Modules")

set(SOURCE_FILES
        main.cpp

        World/Elements/Ant.cpp
        World/Elements/Ant.h
        World/Display/Display.cpp
        World/Display/Display.h
        World/Elements/Grid3D.cpp
        World/Elements/Grid3D.h
        World/Elements/Unit.cpp
        World/Elements/Unit.h
        World/World.cpp
        World/World.h)

add_executable(langton3D ${SOURCE_FILES})

include_directories(commun /usr/local/include/)
link_directories(/usr/local/lib/)