cmake_minimum_required(VERSION 2.8)

project(langton3D)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{SFML_ROOT}/cmake/Modules")

include_directories(commun ${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Add all source files in the project
file(GLOB_RECURSE
        SOURCE_FILES
        simulation/*.cpp)

set(GLAD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)

find_package(glfw3 3.2 REQUIRED)

# Principal target
add_executable(langton3D ${SOURCE_FILES} ${GLAD_SOURCES} main.cpp)

target_link_libraries(langton3D glfw)

add_custom_command(TARGET langton3D PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/simulation/Rendering/Shaders $<TARGET_FILE_DIR:langton3D>/Shaders)
