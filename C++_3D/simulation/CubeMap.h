//
// Created by benji on 16/11/16.
//

#ifndef LANGTON3D_CUBEMAP_H
#define LANGTON3D_CUBEMAP_H

#include <glm/detail/type_vec3.hpp>
#include <map>
#include <memory>

#include "Elements/Unit.h"
#include "Rendering/RenderableCube.h"


struct Cube;
struct Vector3;


typedef std::map<Vector3, std::shared_ptr<Cube>> CubeMap;
typedef CubeMap::iterator CubeMapIterator;

struct Vector3 {
    Vector3(const int posX, const int posY, const int posZ);

    int squareLength() const {return x*x + y*y + z*z;}

    bool less(const Vector3 &other) const;

    bool equal(const Vector3 &other) const;

    Vector3& operator+=(const Vector3 &other);

    glm::vec3 toGlmVec3() {return glm::vec3(x, y, z);}

    int x, y, z;
};

constexpr bool operator==(Vector3 const& u, Vector3 const& v) {return u.equal(v);}
constexpr bool operator!=(Vector3 const& u, Vector3 const& v) {return !(u==v);}
constexpr bool operator< (Vector3 const& u, Vector3 const& v) {return u.less(v);}
constexpr bool operator<=(Vector3 const& u, Vector3 const& v) {return u<v || u==v;}
constexpr bool operator>=(Vector3 const& u, Vector3 const& v) {return !(u<v);}
constexpr bool operator> (Vector3 const& u, Vector3 const& v) {return u>=v && u!=v;}
//Vector3 operator+(Vector3 const& u, Vector3 const& v){Vector3 r=u; r+=v; return r;}



struct Cube {
    static Color nextColor(Color color);

    Cube(Color color, float alpha,
         glm::vec3 ambient  = glm::vec3(0.85f, 0.25f, 0.1f),
         glm::vec3 diffuse  = glm::vec3(0.85f, 0.75f, 0.1f),
         glm::vec3 specular = glm::vec3(0.0f,  0.0f, 0.0f));

    void render(Context *context, Vector3 position);

    std::shared_ptr<RenderableCube> _render = nullptr;

    float getAlpha();
    void setAlpha(float alpha);

    Color _color;
};


#endif //LANGTON3D_CUBEMAP_H
