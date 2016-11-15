//
// Created by benji on 07/11/16.
//

#include <cassert>
#include <fstream>
#include <iostream>
#include "Shader.h"

Shader Shader::loadFromFile(std::string filename, GLenum shaderType) {
    std::ifstream fileStream(filename);

    std::string shaderCode = "";
    std::string line;

    if (fileStream.is_open()) {
        while (getline(fileStream, line)) {
            shaderCode += line + "\n";
        }
        fileStream.close();
    }
    else throw std::runtime_error("Unable to read the stream.");

    return Shader(shaderCode, shaderType);
}

Shader::Shader(const std::string& shaderCode, GLenum shaderType) : _id(0), _shaderType(shaderType) {

    // Create the shader object
    _id = glCreateShader(_shaderType);
    if(_id == 0)
        throw std::runtime_error("glCreateShader failed");

    // Set the source code
    const char* source = shaderCode.c_str();
    glShaderSource(_id, 1, &source, nullptr);

    // Compile
    glCompileShader(_id);

    // Throw exception if compile error occurred
    GLint status;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(_id, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(_id); _id = 0;
        throw std::runtime_error(msg);
    }

    _refCount = std::make_shared<int>(1);
}

Shader::Shader(const Shader &other) {
    this->_id = other.getID();
    this->_refCount = other._refCount;
    assert(_refCount);
    *this->_refCount += 1;
}

Shader::~Shader() {
    *this->_refCount -= 1;
    if (*this->_refCount == 0) {
        glDeleteShader(_id);
    }
}