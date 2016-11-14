//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_PROGRAM_H
#define LANGTON3D_PROGRAM_H


#include <vector>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec3.hpp>

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

    void setUniformMatrix4(const GLchar * uniformName, glm::mat4 &matrix);
    void setUniform3f (const GLchar *uniformName, const GLfloat &x, const GLfloat &y, const GLfloat &z);
    void setUniform1i (const GLchar *uniformName, const GLint &value);
    void setUniform1f (const GLchar *uniformName, const GLfloat &value);
    void setUniform4f (const GLchar *uniformName, const GLfloat &x, const GLfloat &y, const GLfloat &z, GLfloat &t);
    void setUniform3fv(const GLchar *uniformName, const GLsizei count, const GLfloat *array);

    void setUniform(const GLchar* uniformName, const GLfloat &value);
    void setUniform(const GLchar* uniformName, const glm::vec3 &v);

private :
    GLuint _id;
};


#endif //LANGTON3D_PROGRAM_H
