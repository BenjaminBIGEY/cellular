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

void RenderableCube::render(Context *context) {
    if (!_compiled) buildModelData(context);

    //Translation
    glm::mat4x4 model = glm::translate(glm::mat4x4(), glm::tvec3<float>(this->_x, this->_y, this->_z));
    context->program().setUniformMatrix4((GLchar*)"model", model);

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
    const int floatPerTexCoord = 2;
    const int floatPerColor = 4;

    // Calculation of points on the cube
    const int vertBufferSize = floatPerVert * size;
    const int normBufferSize = floatPerNorm * size;
    const int texCoordBufferSize = floatPerTexCoord * size;
    const int colorBufferSize = floatPerColor * size;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     const GLfloat vertices[vertBufferSize] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end

            1.0f,-1.0f, 1.0f, // Face 2
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f,-1.0f,-1.0f, // Face 3
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f, 1.0f, 1.0f, // Face 4
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,

            1.0f,-1.0f,-1.0f, // Face 5
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,

            1.0f, 1.0f, 1.0f, // Face 6
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    GLfloat* normals = new GLfloat[normBufferSize];
    GLfloat normalizer;
    for(int i = 0 ; i < vertBufferSize ; i++) {
        if(i%3 == 0)
            normalizer = (GLfloat)sqrt(vertices[i%3] *   vertices[i%3]
                                     + vertices[i%3+1] * vertices[i%3+1]
                                     + vertices[i%3+2] * vertices[i%3+2]);

        normals[i] = vertices[i] / normalizer;
    }

    GLfloat* colors = new GLfloat[colorBufferSize];
    for(int i = 0 ; i < colorBufferSize ; i++) {
        colors[i] = i%4 == 0 ? _r : (i%4 == 1 ? _g : (i%4 == 2 ? _b : _a)); // {r, g, b, a, r, g, b, ...}
    }

    GLfloat* texCoords = new GLfloat[texCoordBufferSize]; // TODO

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

        glEnableVertexAttribArray((GLuint)context->program().attrib("vertNorm"));
        glVertexAttribPointer((GLuint)context->program().attrib("vertNorm"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


    // Tex coords
    bool texturesExisting = false;
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
        if(!texturesExisting) { // Colors
            glBufferData(GL_ARRAY_BUFFER, colorBufferSize * sizeof(GLfloat), colors, GL_STATIC_DRAW);

            glEnableVertexAttribArray((GLuint)context->program().attrib("vertColor"));
            glVertexAttribPointer((GLuint)context->program().attrib("vertColor"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        } else {
            glBufferData(GL_ARRAY_BUFFER, texCoordBufferSize * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

            glEnableVertexAttribArray((GLuint)context->program().attrib("vertTexCoord"));
            glVertexAttribPointer((GLuint)context->program().attrib("vertTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        }

    // End
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    delete[] normals;
    delete[] colors;
    delete[] texCoords;


    _compiled = true;

    this->loadTextures();
}