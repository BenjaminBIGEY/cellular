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

RenderableCube::RenderableCube(float length) :
        RenderableModel(), _length(length) {
}

void RenderableCube::render(Context *context) {
    if (!_compiled) buildModelData(context);

    //Translation
    glm::mat4x4 model = glm::translate(glm::mat4x4(), glm::tvec3<float>(this->_x, this->_y, this->_z));
    context->program().setUniformMatrix4("model", model);

    context->pushMaterial(this->_material);

    glBindVertexArray(this->_gVAO);

    glDrawArrays(GL_TRIANGLES, 0, 12);

    glBindVertexArray(0);
}

void RenderableCube::buildModelData(Context *context) {
    /*const int vertPerFace = 6;
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
    }

    //Traitement openGL
    regenerateBuffers();

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertBufferSize * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(context->program().attrib("vert"));
    glVertexAttribPointer(context->program().attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normBufferSize * sizeof(float), normals, GL_STATIC_DRAW);

    glEnableVertexAttribArray(context->program().attrib("vertNorm"));
    glVertexAttribPointer(context->program().attrib("vertNorm"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Tex coords
    glBindBuffer(GL_ARRAY_BUFFER, this->texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, texCoordBufferSize * sizeof(float), texCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(context->program().attrib("vertTexCoord"));
    glVertexAttribPointer(context->program().attrib("vertTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Fin
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    delete[] vertices;
    delete[] normals;
    delete[] texCoords;

    this->verticesCount = size;
    _compiled = true;

    this->loadTextures();*/
}