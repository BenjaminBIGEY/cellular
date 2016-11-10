//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLECUBE_H
#define LANGTON3D_RENDERABLECUBE_H


#include "Renderable.h"

class RenderableCube : public RenderableModel {
public :
    RenderableCube();

    virtual void render(Context *context) override;

private :
    void buildModelData(Context *context);
};


#endif //LANGTON3D_RENDERABLECUBE_H
