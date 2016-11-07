//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>

#include "Light.h"
#include "Context.h"
#include "Program.h"

Light::Light(LightType type, float x, float y, float z) :
        _type(type), _x(x), _y(y), _z(z) {

}

void Light::pushLight(Context *context) {
    context->program().setUniform1i("light.type", (int) this->_type);
    context->program().setUniform3f("light.position", this->_x, this->_y, this->_z);
}