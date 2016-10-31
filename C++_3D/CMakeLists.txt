cmake_minimum_required(VERSION 3.6)
project(langton3D)


#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{SFML_ROOT}/cmake/Modules")

# Add all source files in the project
file(GLOB_RECURSE
        SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/World/*.cpp)

find_package(glfw3 3.2 REQUIRED)


# Principal target

add_executable(langton3D ${SOURCE_FILES} main.cpp)

target_link_libraries(langton3D GL GLU GLEW glfw X11 pthread) #glfw3

include_directories(commun /usr/local/include)


link_directories(/usr/local/lib/)