#include <iostream>
//#include "World/World.h"

// GLEW
#define GLEW_STATIC
//#include "World/Display/glew.h"
#include <GL/glew.h>
// GLFW
//#include "World/Display/glfw3.h"
#include <GLFW/glfw3.h>


int main(int argc, char** argv) {
    /*glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/
    /*World world(10, 10, 10);
    world.addAnt(5, 5, 5);

    for(int i = 0 ; i < 100 ; i++) {
        world.update(200000); // update toutes les 0.2s
    }*/




    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    return 0;
}