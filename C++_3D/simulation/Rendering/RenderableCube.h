//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLECUBE_H
#define LANGTON3D_RENDERABLECUBE_H


#include "Renderable.h"

class RenderableCube : public RenderableModel {
public :
    // Red, Green, Blue, Alpha components for the cube color
    RenderableCube(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 0.8);
    RenderableCube(glm::vec4 color);


    virtual void render(Context *context) override;

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 0.8);
    void setColor(glm::vec4 c);

private :
    void buildModelData(Context *context);

    GLfloat _r, _g, _b, _a; // red, green, blue, alpha components
};


#endif //LANGTON3D_RENDERABLECUBE_H
