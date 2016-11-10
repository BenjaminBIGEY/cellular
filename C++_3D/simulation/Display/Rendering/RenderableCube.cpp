//
// Created by benji on 07/11/16.
//

#include <math.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Renderable.h"
#include "Context.h"
#include "RenderableCube.h"

RenderableCube::RenderableCube() : RenderableModel() {
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
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };


/*



    const int vertPerFace = 6;
    const int floatPerVert = 3;
    const int floatPerNorm = 3;
    const int floatPerTexCoord = 2;
    const int size = vertPerFace * (ringCount + 1) * segmentCount;

    //Calcul des points de la sphère
    const int vertBufferSize = floatPerVert * size;
    float* vertices = new float[vertBufferSize];

    const int normBufferSize = floatPerNorm * size;
    float* normals = new float[normBufferSize];

    int texCoordBufferSize = floatPerTexCoord * size;
    float* texCoords = new float[texCoordBufferSize];

    for (int i = 0 ; i < segmentCount ; i++) {
        for (int j = 0 ; j < ringCount + 1 ; j++) {
            int index = i * (ringCount + 1) + j;

            //POSITION

            //Angle dans le sens direct
            double alpha1 = i / (double) segmentCount * M_PI * 2;
            double alpha2 = (i + 1) / (double) segmentCount * M_PI * 2;
            //Angle du haut vers le bas
            double beta1 = j / (double) (ringCount + 1) * M_PI;
            double beta2 = (j+1) / (double) (ringCount + 1) * M_PI;

            double z14 = cos(beta1) * radius;
            double z23 = cos(beta2) * radius;
            double x1 = cos(alpha1) * sin(beta1) * radius;
            double x2 = cos(alpha1) * sin(beta2) * radius;
            double x3 = cos(alpha2) * sin(beta2) * radius;
            double x4 = cos(alpha2) * sin(beta1) * radius;
            double y1 = sin(alpha1) * sin(beta1) * radius;
            double y2 = sin(alpha1) * sin(beta2) * radius;
            double y3 = sin(alpha2) * sin(beta2) * radius;
            double y4 = sin(alpha2) * sin(beta1) * radius;

            int vIndex = floatPerVert * vertPerFace * index;

            vertices[vIndex] = (float) x1;
            vertices[vIndex + 1] = (float) y1;
            vertices[vIndex + 2] = (float) z14;

            vertices[vIndex + 3] = (float) x2;
            vertices[vIndex + 4] = (float) y2;
            vertices[vIndex + 5] = (float) z23;

            vertices[vIndex + 6] = (float) x3;
            vertices[vIndex + 7] = (float) y3;
            vertices[vIndex + 8] = (float) z23;

            vertices[vIndex + 9] = (float) x1;
            vertices[vIndex + 10] = (float) y1;
            vertices[vIndex + 11] = (float) z14;

            vertices[vIndex + 12] = (float) x3;
            vertices[vIndex + 13] = (float) y3;
            vertices[vIndex + 14] = (float) z23;

            vertices[vIndex + 15] = (float) x4;
            vertices[vIndex + 16] = (float) y4;
            vertices[vIndex + 17] = (float) z14;

            //NORMALES

            normals[vIndex] = (float) (x1 / radius);
            normals[vIndex + 1] = (float) (y1 / radius);
            normals[vIndex + 2] = (float) (z14 / radius);

            normals[vIndex + 3] = (float) (x2 / radius);
            normals[vIndex + 4] = (float) (y2 / radius);
            normals[vIndex + 5] = (float) (z23 / radius);

            normals[vIndex + 6] = (float) (x3 / radius);
            normals[vIndex + 7] = (float) (y3 / radius);
            normals[vIndex + 8] = (float) (z23 / radius);

            normals[vIndex + 9] = (float) (x1 / radius);
            normals[vIndex + 10] = (float) (y1 / radius);
            normals[vIndex + 11] = (float) (z14 / radius);

            normals[vIndex + 12] = (float) (x3 / radius);
            normals[vIndex + 13] = (float) (y3 / radius);
            normals[vIndex + 14] = (float) (z23 / radius);

            normals[vIndex + 15] = (float) (x4 / radius);
            normals[vIndex + 16] = (float) (y4 / radius);
            normals[vIndex + 17] = (float) (z14 / radius);

            //COORDONNEES DE TEXTURE
            int texIndex = vertPerFace * index * floatPerTexCoord;
            texCoords[texIndex] = (float) i / segmentCount;
            texCoords[texIndex + 1] = (float) j / ringCount;

            texCoords[texIndex + 2] = (float) i / segmentCount;
            texCoords[texIndex + 3] = (float) (j+1) / ringCount;

            texCoords[texIndex + 4] = (float) (i+1) / segmentCount;
            texCoords[texIndex + 5] = (float) (j+1) / ringCount;

            texCoords[texIndex + 6] = (float) i / segmentCount;
            texCoords[texIndex + 7] = (float) j / ringCount;

            texCoords[texIndex + 8] = (float) (i+1) / segmentCount;
            texCoords[texIndex + 9] = (float) (j+1) / ringCount;

            texCoords[texIndex + 10] = (float) (i+1) / segmentCount;
            texCoords[texIndex + 11] = (float) j / ringCount;
        }
    }*/

    //Traitement openGL
    regenerateBuffers();

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(context->program().attrib("vert"));
    glVertexAttribPointer(context->program().attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    //Tex coords
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), g_color_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(context->program().attrib("vertTexCoord"));
    glVertexAttribPointer(context->program().attrib("vertTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Fin
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //delete[] g_vertex_buffer_data;
    //delete[] g_color_buffer_data;


    _compiled = true;

    this->loadTextures();
}