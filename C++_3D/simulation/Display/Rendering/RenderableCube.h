//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLECUBE_H
#define LANGTON3D_RENDERABLECUBE_H


#include "Renderable.h"

class RenderableCube : public RenderableModel {
public :
    RenderableCube(float length = 1);

    virtual void render(Context *context) override;

private :
    /// Calcule les points du modèle de la sphère et crée un
    /// buffer openGL qui accueille les données.
    void buildModelData(Context *context);

    float _length = 1;
};


#endif //LANGTON3D_RENDERABLECUBE_H
