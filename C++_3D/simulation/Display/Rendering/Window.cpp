//
// Created by benji on 10/11/16.
//

#include "Window.h"
#include "Context.h"


void glfwErrorCallback(int error, const char* description) {
    std::cerr << "There was a glfw error : " << description << std::endl;
}


Window::Window() {
    std::cout << "Starting  GLFW" << std::endl;

    // Init GLFW
    if(!glfwInit()) {
        std::cerr << "Error during glfw initializing" << std::endl;
        return;
    }

    glfwSetErrorCallback(glfwErrorCallback);

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(800, 600, "project : Langton 3D", nullptr, nullptr);

    if (!_window) {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    _context = std::make_unique<Context>(_window);

    glEnable(GL_MULTISAMPLE);
}

Window::~Window() {
    destroy();
}

void Window::destroy() {
    if(_destroyed) return;

    _destroyed = true;
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Window::isWindowOpened() {
    return !glfwWindowShouldClose(_window);
}

void Window::setKeyCallback(GLFWkeyfun func) {
    glfwSetKeyCallback(_window, func);
}

void Window::setScrollCallback(GLFWscrollfun func) {
    glfwSetScrollCallback(_window, func);
}

void Window::setupFrame() {
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::finalizeFrame() {
    glfwSwapBuffers(_window);
    glfwPollEvents();
}