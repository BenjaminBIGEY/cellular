//
// Created by benji on 07/11/16.
//

#include <vector>
#include <glad/glad.h>

#include "Context.h"
#include "Light.h"
#include "Material.h"
#include "Shader.h"


Context::Context(GLFWwindow *window) : _window(window) {
    loadProgram("colored", "Shaders/colored_vertex_shader.glslv", "Shaders/colored_fragment_shader.glslf");
    //loadProgram("lighted", "Shaders/lighted_vertex_shader.glslv", "Shaders/lighted_fragment_shader.glslf");

    setCurrentProgram("colored");
}


void Context::setWindow(GLFWwindow *window) {
    this->_window = window;
}

void Context::getWindowDimensions(int &width, int &height) {
    glfwGetFramebufferSize(this->_window, &width, &height);
}

void Context::pushLight(Light &light) {
    light.pushLight(this);
}

void Context::pushMaterial(Material &material) {
    material.pushMaterial(this);
}

void Context::setCurrentProgram(std::string currentProgramID) {
    this->_currentProgram = currentProgramID;

    this->program().use();
}

void Context::loadProgram(std::string name, std::string vertexShader, std::string fragmentShader) {
    std::vector<Shader> shaders;
    shaders.push_back(Shader::loadFromFile(vertexShader, GL_VERTEX_SHADER));
    shaders.push_back(Shader::loadFromFile(fragmentShader, GL_FRAGMENT_SHADER));
    this->_programMap[name] = std::make_shared<Program>(shaders);
}