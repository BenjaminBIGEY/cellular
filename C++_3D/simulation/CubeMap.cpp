//
// Created by benji on 16/11/16.
//

#include "CubeMap.h"


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

void Cube::render(Context *context, glm::vec3 position) {
    _render->render(context, position);
}

float Cube::getAlpha() {
    return _render->getColor().a;
}

void Cube::setAlpha(float alpha) {
    _render->setColor(glm::vec4(glm::vec3(_render->getColor()), alpha));
}