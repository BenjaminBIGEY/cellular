//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_WINDOW_H
#define LANGTON3D_WINDOW_H

#include <iostream>
#include <bits/unique_ptr.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Context;

class Window {
public:
    Window();
    virtual ~Window();

    void destroy();

    bool isWindowOpened();

    void setKeyCallback(GLFWkeyfun func);
    void setScrollCallback(GLFWscrollfun func);

    void setupFrame();
    void finalizeFrame();

    Context * context() {return _context.get();};
    GLFWwindow * const window() {return _window;};
private:
    GLFWwindow* _window = nullptr;
    bool _destroyed = false;

    std::unique_ptr<Context> _context;
};


#endif //LANGTON3D_WINDOW_H
