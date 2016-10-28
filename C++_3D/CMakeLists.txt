cmake_minimum_required(VERSION 3.6)
project(langton3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{SFML_ROOT}/cmake/Modules")

set(SOURCE_FILES
        main.cpp

        World/Display/Display.cpp
        World/Display/Display.h
        #World/Display/glew.h
        #World/Display/glfw3.h

        World/Elements/Ant.cpp
        World/Elements/Ant.h
        World/Elements/Grid3D.cpp
        World/Elements/Grid3D.h
        World/Elements/Unit.cpp
        World/Elements/Unit.h

        World/World.cpp
        World/World.h)

add_executable(langton3D ${SOURCE_FILES})

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew PATHS ${GLEW_LOCATION}/lib
        $ENV{GLEW_LOCATION}/lib
        /usr/lib64
        /usr/lib)# PATH_SUFFIXES lib64)

#find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories($(GLEW_INCLUDE_DIRS))
    link_libraries(${GLEW_LIBRARIES})
    target_link_libraries(${GLEW_LIBRARIES})
endif()


include_directories(commun /usr/local/include)
link_directories(/usr/local/lib/)