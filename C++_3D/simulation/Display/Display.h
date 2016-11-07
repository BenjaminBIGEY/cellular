//
// Created by benji on 24/10/16.
//

#ifndef C_3D_DISPLAY_H
#define C_3D_DISPLAY_H

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <bits/unique_ptr.h>
#include <memory>
#include <unistd.h>

#include "FileBuffer.h"
#include "Rendering/Context.h"
#include "Rendering/Renderable.h"
#include "Rendering/RenderableCube.h"
#include "Rendering/Scene.h"

/*
enum Colors {
    TRANSPARENT = 0,
    WHITE,
    BLACK,
    ORANGE,
    PURPLE,
    YELLOW,
    BLUE,
    GREEN,
    RED,
    BROWN
};*/

class Display {
public:
    Display();
    bool initGL(); // return false if something is
    void initGrid(int sizeX, int sizeY, int sizeZ/*, Colors color = TRANSPARENT*/);

    void update();

    bool isWindowOpened();

    void debug();

private:
    static void glfwErrorCallback(int error, const char* description);
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* _window = nullptr;
    std::unique_ptr<Scene> _scene = nullptr;


    int _width, _height;
};


#endif //C_3D_DISPLAY_H
