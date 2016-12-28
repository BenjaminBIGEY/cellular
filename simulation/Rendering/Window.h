//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_WINDOW_H
#define LANGTON3D_WINDOW_H

#include <bits/unique_ptr.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Message_Colors.h"

class Context;

class Window {
public:
    Window(std::string title);
    virtual ~Window();

    void setTitle(std::string newTitle);

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
