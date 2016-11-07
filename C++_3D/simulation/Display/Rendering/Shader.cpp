//
// Created by benji on 07/11/16.
//

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

Shader::Shader(std::string& shaderCode, GLenum shaderType) : _id(0), _shaderType(_shaderType) {

    _id = glCreateShader(_shaderType);

    const char* source = shaderCode.c_str();
    glShaderSource(_id, 1, &source, nullptr);

    glCompileShader(_id);

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
    *this->_refCount += 1;
}

Shader::~Shader() {
    *this->_refCount -= 1;
    if (*this->_refCount == 0) {
        glDeleteShader(_id);
    }
}