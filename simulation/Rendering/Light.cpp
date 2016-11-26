//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>
#include <sstream>

#include "Light.h"

void Light::addLight(lightInfos light) {
    _listLights.push_back(light);
}

void Light::addLight(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, float ambientCoeff) {
    addLight({glm::vec3(x, y, z), glm::vec3(r, g, b), ambientCoeff});
}

void Light::addLight(glm::vec3 position, glm::vec3 color, float ambientCoeff) {
    addLight({position, color, ambientCoeff});
}

void Light::pushLight(Context *context) {
    GLint numLights = (GLint)_listLights.size();
    context->program().setUniform1i((GLchar*)"numLights", numLights);

    for(int i = 0 ; i < numLights ; i++) {
        setLightUniform(context, "position",     i, _listLights[i]._position);
        setLightUniform(context, "color",        i, _listLights[i]._color);
        setLightUniform(context, "ambientCoeff", i, _listLights[i]._ambientCoeff);
    }
}

template <typename T>
void Light::setLightUniform(Context *context, const std::string propertyName, GLint lightIndex, const T& value) {

    std::ostringstream ss;
    ss << "allLights[" << lightIndex << "]." << propertyName;
    std::string uniformName = ss.str();

    context->program().setUniform(uniformName.c_str(), value);
}