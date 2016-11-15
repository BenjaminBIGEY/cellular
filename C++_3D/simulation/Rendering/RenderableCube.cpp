//
// Created by benji on 07/11/16.
//

#include <math.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Context.h"
#include "RenderableCube.h"

RenderableCube::RenderableCube(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : RenderableModel() {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

RenderableCube::RenderableCube(glm::vec4 c) : RenderableCube(c.r, c.g, c.b, c.a) {}

void RenderableCube::render(Context *context) {
    if (!_compiled) buildModelData(context);

    //Translation
    glm::mat4x4 model = glm::translate(glm::mat4x4(), glm::tvec3<float>(this->_x, this->_y, this->_z));
    context->program().setUniformMatrix4((GLchar*)"model", model);

    // Wood shininess
    context->program().setUniform1f((GLchar*)"materialShininess", 80.0);
    context->program().setUniform3f((GLchar*)"materialSpecularColor", 1.0f, 1.0f, 1.0f);

    context->pushMaterial(this->_material);

    glBindVertexArray(this->_gVAO);

    glDrawArrays(GL_TRIANGLES, 0, 36); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

    glBindVertexArray(0);
}

void RenderableCube::buildModelData(Context *context) {
    /**
     * Points declarations
     */
    const int nbrFaces = 6;
    const int trianglePerFace = 2;
    const int vertPerTriangle = 3;
    const int size = nbrFaces * trianglePerFace * vertPerTriangle;

    const int floatPerVert = 3;
    const int floatPerNorm = 3;
    const int floatPerColor = 4;

    // Calculation of points on the cube
    const int vertBufferSize = floatPerVert * size;
    const int normBufferSize = floatPerNorm * size;
    const int colorBufferSize = floatPerColor * size;


    const GLfloat vertices[vertBufferSize] = {
            //  X     Y     Z
            // bottom
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            // top
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f,  1.0f,
             1.0f, 1.0f, -1.0f,
             1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f,  1.0f,
             1.0f, 1.0f,  1.0f,

            // front
            -1.0f, -1.0f, 1.0f,
             1.0f, -1.0f, 1.0f,
            -1.0f,  1.0f, 1.0f,
             1.0f, -1.0f, 1.0f,
             1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f, 1.0f,

            // back
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,

            // left
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            // right
            1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f
    };

    const GLfloat normals[normBufferSize] = {
            //    Normal
            // bottom
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,

            // top
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            // front
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            // back
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            // left
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            // right
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
    };

    GLfloat* colors = new GLfloat[colorBufferSize];
    for(int i = 0 ; i < colorBufferSize ; i++) {
        colors[i] = i%4 == 0 ? _r : (i%4 == 1 ? _g : (i%4 == 2 ? _b : _a)); // {r, g, b, a, r, g, b, ...}
    }

    /**
     * OpenGL treatment
     */
    regenerateBuffers();

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertBufferSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray((GLuint)context->program().attrib("vert"));
        glVertexAttribPointer((GLuint)context->program().attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normBufferSize * sizeof(GLfloat), normals, GL_STATIC_DRAW);

        glEnableVertexAttribArray((GLuint)context->program().attrib("vertNormal"));
        glVertexAttribPointer((GLuint)context->program().attrib("vertNormal"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, _colorCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, colorBufferSize * sizeof(GLfloat), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray((GLuint)context->program().attrib("vertColor"));
        glVertexAttribPointer((GLuint)context->program().attrib("vertColor"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // End
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //delete[] normals;
    delete[] colors;


    _compiled = true;

    //this->loadTextures();
}

void RenderableCube::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

void RenderableCube::setColor(glm::vec4 c) {
    setColor(c.r, c.g, c.b, c.a);
}