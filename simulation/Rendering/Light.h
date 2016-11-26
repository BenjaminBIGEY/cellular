//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_LIGHT_H
#define LANGTON3D_LIGHT_H

#include <glm/glm.hpp>
#include <vector>

#include "Context.h"

class Context;

struct lightInfos {
    glm::vec3 _position;
    glm::vec3 _color;
    float _ambientCoeff;
};

class Light {
public :
    Light(){}
    void addLight(lightInfos light);
    void addLight(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, float ambientCoeff);
    void addLight(glm::vec3 position, glm::vec3 color, float ambientCoeff);

    void pushLight(Context *context);

private :
    template <typename T>
    void setLightUniform(Context *context, const std::string propertyName, GLint lightIndex, const T& value);

    std::vector<lightInfos> _listLights;
};


#endif //LANGTON3D_LIGHT_H