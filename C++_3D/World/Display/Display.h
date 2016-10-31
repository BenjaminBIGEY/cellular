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
#include <GLFW/glfw3.h>
//#include <bits/unique_ptr.h>
#include <memory>

#include <unistd.h>



class Display {
public:
    Display(){};
    bool initGL(); // return false if something is

    void update();

    bool isWindowOpened();

private:
    static void glfwErrorCallback(int error, const char* description);
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLFWwindow* _window = nullptr;

    int _width, _height;
};


#endif //C_3D_DISPLAY_H
