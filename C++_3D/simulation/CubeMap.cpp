//
// Created by benji on 16/11/16.
//

#include "CubeMap.h"

Vector3::Vector3(const int posX, const int posY, const int posZ) {
    x = posX;
    y = posY;
    z = posZ;
}

bool Vector3::less(const Vector3 &other) const {
    if(this->squareLength() == other.squareLength()) {
        // distance egal beetween origin and u / v : comparison of x, y, z components
        return this->x < other.x ? true : this->y < other.y ? true : this->z < other.z;
    }
    return this->squareLength() < other.squareLength();
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

Color Cube::nextColor(Color color) {
    Color next_color = (Color)((int)color + 1);

    if (next_color == Color::NBR) {
        return (Color)0;
    } else {
        return next_color;
    }
}

Cube::Cube(Color color, float alpha, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    _color = color;

    // Graphic part
    _render = std::make_shared<RenderableCube>(glm::vec4(Unit::getColor(color), alpha));
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