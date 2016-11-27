//
// Created by benji on 16/11/16.
//

#include "CubeMap.h"
#include <iostream>

Vector3::Vector3(const int posX, const int posY, const int posZ) {
    x = posX;
    y = posY;
    z = posZ;
}

Vector3::Vector3(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

bool Vector3::less(const Vector3 &other) const {
    return std::tie(this->x, this->y, this->z) < std::tie(other.x, other.y, other.z);
}

bool Vector3::equal(const Vector3 &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

Vector3& Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Cube::Cube(Color color, float alpha, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : _color(color) {
    // Graphic part
    _render = std::make_shared<RenderableCube>(glm::vec4(color.getColorGraphic(), alpha));
    _render->getMaterial().setAmbient(ambient.x, ambient.y, ambient.z);
    _render->getMaterial().setDiffuse(diffuse.x, diffuse.y, diffuse.z);
    _render->getMaterial().setSpecular(specular.x, specular.y, specular.z);
}

void Cube::render(Context *context, Vector3 position) {
    _render->render(context, position.toGlmVec3());
}

float Cube::getAlpha() {
    return _render->getColor().a;
}

void Cube::setAlpha(float alpha) {
    _render->setColor(glm::vec4(glm::vec3(_render->getColor()), alpha));
}