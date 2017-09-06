//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>

#include "Material.h"
#include "Context.h"

Material::Material(float diffuseR, float diffuseG, float diffuseB, float specularR, float specularG, float specularB,
                   float ambientR, float ambientG, float ambientB) :
        _diffuseR(diffuseR),   _diffuseG(diffuseG),   _diffuseB(diffuseB),
        _specularR(specularR), _specularG(specularG), _specularB(specularB),
        _ambientR(ambientR),   _ambientG(ambientG),   _ambientB(ambientB),
        _specularIntensity(0.5), _specularHardness(5), _shininess(80.0) {

}

void Material::setDiffuse(float r, float g, float b) {
    _diffuseR = r;
    _diffuseG = g;
    _diffuseB = b;
}

void Material::setSpecular(float r, float g, float b) {
    _specularR = r;
    _specularG = g;
    _specularB = b;
}

void Material::setSpecularParameters(float intensity, float hardness) {
    _specularIntensity = intensity;
    _specularHardness = hardness;
}

void Material::setAmbient(float r, float g, float b) {
    _ambientR = r;
    _ambientG = g;
    _ambientB = b;
}

void Material::setShininess(float shininess) {
    _shininess = shininess;
}

void Material::pushMaterial(Context * context) {
    glBindTexture(GL_TEXTURE_2D, 0);

    context->program().setUniform3f((GLchar*)"material.ambientColor", _ambientR, _ambientG, _ambientB);
    context->program().setUniform3f((GLchar*)"material.diffuseColor", _diffuseR, _diffuseG, _diffuseB);
    context->program().setUniform3f((GLchar*)"material.specularColor", _specularR, _specularG, _specularB);

    context->program().setUniform1f((GLchar*)"material.specularIntensity", _specularIntensity);
    context->program().setUniform1f((GLchar*)"material.specularHardness", _specularHardness);

    context->program().setUniform1f((GLchar*)"material.shininess", _shininess);
}