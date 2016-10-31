//
// Created by benji on 24/10/16.
//

#include "Display.h"

bool Display::initGL() {
    std::cout << "Starting  GLFW" << std::endl;

    // Init GLFW
    if(!glfwInit()) {
        std::cerr << "Error during glfw initializing" << std::endl;
        return false;
    }
    glfwSetErrorCallback(glfwErrorCallback);

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(800, 600, "project : Langton 3D", nullptr, nullptr);

    if (_window == nullptr) {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    // Set the required callback functions
    glfwSetKeyCallback(_window, glfwKeyCallback);

    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);






    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return false;
    }

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);

    return true;
}

void Display::update() {
    glfwGetFramebufferSize(_window, &_width, &_height);
    glViewport(0, 0, _width, _height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glfwSwapBuffers(_window);
    glfwPollEvents();
    std::cout << "boucle de display" << std::endl;
}

bool Display::isWindowOpened() {
    return !glfwWindowShouldClose(_window);
}

/*
 * Callbacks definition
 */
void Display::glfwErrorCallback(int error, const char* description) {
    std::cerr << "There was a glfw error : " << description << std::endl;
}

// Is called whenever a key is pressed/released via GLFW
void Display::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
/* EXAMPLES :
    if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
        auto traveling = std::make_unique<Traveling>(
                scene->camera(), 0, 0, 30, 0, 0, 0, 0, 1, 0
        );
        traveling->setDuration(0.5f);
        scene->camera().traveling(traveling);
    }
    else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
        auto traveling = std::make_unique<Traveling>(
                scene->camera(), 15, 15, 15, 0, 0, 0, 0, 0, 1
        );
        traveling->setDuration(0.5f);
        scene->camera().traveling(traveling);
    }*/
}