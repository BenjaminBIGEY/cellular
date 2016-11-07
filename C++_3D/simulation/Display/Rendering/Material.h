//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_MATERIAL_H
#define LANGTON3D_MATERIAL_H


#include <vector>
#include "Texture.h"

class Context;

class Material {

public :
    Material(float diffuseR = 0.8f, float diffuseG = 0.8f, float diffuseB = 0.8f,
        float specularR = 1.0f, float specularG = 1.0f, float specularB = 1.0f,
        float ambientR = 0.2f, float ambientG = 0.2f, float ambientB = 0.2f);

    void removeAllTextures();
    void addTexture(Texture texture);

    void setDiffuse(float r, float g, float b);

    void setSpecular(float r, float g, float b);
    void setSpecularParameters(float intensity, float hardness);

    void setAmbient(float r, float g, float b);

    void setEmit(bool emit) {
        this->_emit = emit;
    }

    void pushMaterial(Context * context);

private :
    std::vector<Texture> textures;

    float _diffuseR, _diffuseG, _diffuseB;
    float _specularR, _specularG, _specularB;
    float _ambientR, _ambientG, _ambientB;

    float _specularIntensity;
    float _specularHardness;

    bool _emit;
};


#endif //LANGTON3D_MATERIAL_H
