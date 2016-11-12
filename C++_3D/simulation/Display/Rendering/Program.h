//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_PROGRAM_H
#define LANGTON3D_PROGRAM_H


#include <vector>
#include <glm/detail/type_mat.hpp>

#include "Shader.h"

class Program {
public :
    Program(const std::vector<Shader>& shaders);
    Program(const Program &other);
    ~Program();

    void addShader(Shader & shader);
    void removeShader(Shader & shader);

    void use() const;
    bool isInUse() const;
    void stopUsing() const;

    GLint attrib(const GLchar* attribName);
    GLint uniform(const GLchar* uniformName);

    void setUniformMatrix4(GLchar * uniformName, glm::mat4 &matrix);
    void setUniform3f(GLchar *uniformName, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void setUniform1i(GLchar *uniformName, const GLint &value);
    void setUniform1f(GLchar *uniformName, const GLfloat &value);
    void setUniform4f(GLchar *uniformName, const GLfloat &x, const GLfloat &y, const GLfloat &z, GLfloat &t);
private :
    GLuint _id;
};


#endif //LANGTON3D_PROGRAM_H
