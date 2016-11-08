//
// Created by benji on 24/10/16.
//

#include "Display.h"

Display::Display() {

}

Display::~Display() {
    glfwTerminate();
}

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

    if (!_window) {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    // Set the required callback functions
    glfwSetKeyCallback(_window, glfwKeyCallback);
    glfwSetScrollCallback(_window, glfwScrollCallback);

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

void Display::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    _scene->getCamera().zoom((float) pow(1.2, - yoffset));
}

void Display::debug() {
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();


    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);



    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}