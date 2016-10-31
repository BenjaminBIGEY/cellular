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


/*
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}*/


class Display {
public:
    Display();
    bool initGL(); // return false if something is wrong
    /*void initGL();
    void display();*/

    static void glfwErrorCallback(int error, const char* description);
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
    // Window dimensions
    const GLuint WIDTH = 800, HEIGHT = 600;

    GLFWwindow* _window = nullptr;
};


#endif //C_3D_DISPLAY_H
