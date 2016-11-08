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
#include <memory>
#include <unistd.h>

#include "FileBuffer.h"



template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Display {
public:
    Display();
    ~Display();

    bool initGL(); // return false if something is wrong

    void update();

    bool isWindowOpened();

    void debug();

    GLFWwindow* getWindow(){return _window;}

private:
    static void glfwErrorCallback(int error, const char* description);
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* _window = nullptr;


    int _width, _height;
};


#endif //C_3D_DISPLAY_H
