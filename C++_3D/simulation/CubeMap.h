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
class Vec3Comparator;

typedef std::map<glm::vec3, std::shared_ptr<Cube>, Vec3Comparator> CubeMap;
typedef CubeMap::iterator CubeMapIterator;


class Vec3Comparator {
public:
    bool operator()(const glm::vec3 & u, const glm::vec3 & v) const {
        // distance egal beetween origin and u / v : comparison of x, y, z components
        if(u.length() == v.length()) {
            return u.x < v.x ? true : u.y < v.y ? true : u.z < v.z;
        }
        return u.length() < v.length();
    }
};

struct Cube {
    static Color nextColor(Color color);

    Cube(Color color, float alpha,
         glm::vec3 ambient  = glm::vec3(0.85f, 0.25f, 0.1f),
         glm::vec3 diffuse  = glm::vec3(0.85f, 0.75f, 0.1f),
         glm::vec3 specular = glm::vec3(0.0f,  0.0f, 0.0f));

    void render(Context *context, glm::vec3 position);


    std::shared_ptr<RenderableCube> _render = nullptr;

    float getAlpha();
    void setAlpha(float alpha);

    Color _color;
};


#endif //LANGTON3D_CUBEMAP_H
