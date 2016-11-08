//
// Created by benji on 07/11/16.
//

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Renderable.h"
#include "Context.h"
#include "Texture.h"
#include "Program.h"


Renderable::Renderable() {

}

Renderable::~Renderable() {
    deleteBuffers();
}

void Renderable::regenerateBuffers() {
    deleteBuffers();

    glGenVertexArrays(1, &this->_gVAO);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(this->_gVAO);
}

void Renderable::deleteBuffers() {
    if (this->_gVAO != 0) {
        glDeleteVertexArrays(1, &this->_gVAO);
        this->_gVAO = 0;
    }
}




// -----


RenderableModel::RenderableModel() : Renderable() {

}

RenderableModel::~RenderableModel() {

}

void RenderableModel::setPosition(float x, float y, float z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

glm::vec3 RenderableModel::getPosition() {
    return glm::vec3(this->_x, this->_y, this->_z);
}

void RenderableModel::setMaterial(Material &material) {
    this->_material = material;
    this->_compiled = false;
}

void RenderableModel::addTexturePath(std::string path) {
    this->_texturePaths.push_back(path);
    this->_compiled = false;
}

void RenderableModel::regenerateBuffers() {
    Renderable::regenerateBuffers();

    glGenBuffers(1, &this->_vertexBuffer);
    glGenBuffers(1, &this->_normalBuffer);
    glGenBuffers(1, &this->_texCoordBuffer);
}

void RenderableModel::deleteBuffers() {
    Renderable::deleteBuffers();

    if (this->_vertexBuffer != 0) {
        glDeleteBuffers(1, &this->_vertexBuffer);
        this->_vertexBuffer = 0;
    }

    if (this->_normalBuffer != 0) {
        glDeleteBuffers(1, &this->_normalBuffer);
        this->_normalBuffer = 0;
    }

    if (this->_texCoordBuffer != 0) {
        glDeleteBuffers(1, &this->_texCoordBuffer);
        this->_texCoordBuffer = 0;
    }
}

void RenderableModel::loadTextures() {
    this->_material.removeAllTextures();

    for (std::string & path : this->_texturePaths) {
        this->_material.addTexture(Texture::load(path));
    }
}
