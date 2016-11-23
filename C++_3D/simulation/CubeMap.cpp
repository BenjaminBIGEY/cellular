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

Color Cube::nextColor(Color color) {
    Color next_color = (Color)((int)color + 1);

    if (next_color == Color::NBR) {
        return (Color)0;
    } else {
        return next_color;
    }
}

Cube::Cube(Color color, float alpha) {
    _color = color;

    // Graphic part
    _render = std::make_shared<RenderableCube>(glm::vec4(Unit::getColor(color), alpha));
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