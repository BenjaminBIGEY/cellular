//
// Created by benji on 10/12/16.
//

#ifndef LANGTON3D_VECTOR3_H
#define LANGTON3D_VECTOR3_H

#include <glm/detail/type_vec3.hpp>
#include <memory>

struct Vector3 {
    Vector3(const int posX, const int posY, const int posZ);
    Vector3(const Vector3 &other);

    bool less(const Vector3 &other) const;

    bool equal(const Vector3 &other) const;

    int norm() const;

    Vector3& operator+=(const Vector3 &other);
    Vector3& operator*=(const Vector3 &other);

    glm::vec3 toGlmVec3() {return glm::vec3(x, y, z);}

    int x, y, z;
    
    friend bool operator==(Vector3 const& u, Vector3 const& v) {return u.equal(v);}
    friend bool operator!=(Vector3 const& u, Vector3 const& v) {return !(u==v);}
    friend bool operator< (Vector3 const& u, Vector3 const& v) {return u.less(v);}
    friend bool operator<=(Vector3 const& u, Vector3 const& v) {return u<v || u==v;}
    friend bool operator>=(Vector3 const& u, Vector3 const& v) {return !(u<v);}
    friend bool operator> (Vector3 const& u, Vector3 const& v) {return u>=v && u!=v;}
};




#endif //LANGTON3D_VECTOR3_H
