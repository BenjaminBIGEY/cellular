//
// Created by benji on 10/12/16.
//

#include "Vector3.h"

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
    // ||this|| < ||other|| or (||this|| == ||other|| and this < other)
    int a = this->norm();
    int b = other.norm();
    return std::tie(a) < std::tie(b) or (std::tie(a) == std::tie(b) and std::tie(this->x, this->y, this->z) < std::tie(other.x, other.y, other.z));
}

bool Vector3::equal(const Vector3 &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

int Vector3::norm() const {

    return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector3& Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}