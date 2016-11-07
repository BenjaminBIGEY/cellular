//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_SHADER_H
#define LANGTON3D_SHADER_H


#include <glad/glad.h>
#include <string>
#include <memory>

class Shader {
public :
    static Shader loadFromFile(std::string filename, GLenum shaderType);

    Shader(std::string &shaderCode, GLenum shaderType);
    Shader(const Shader &other);
    virtual ~Shader();

    GLuint getID() const {return _id;}
    GLenum getShaderType() const {return _shaderType;}
private :

    GLuint _id;
    GLenum _shaderType;

    std::shared_ptr<int> _refCount;
};


#endif //LANGTON3D_SHADER_H
