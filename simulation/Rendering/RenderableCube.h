//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLECUBE_H
#define LANGTON3D_RENDERABLECUBE_H


#include "Renderable.h"

class RenderableCube : public RenderableModel {
public :
    // Red, Green, Blue components for the cube color
    RenderableCube(GLfloat r, GLfloat g, GLfloat b);
    RenderableCube(glm::vec3 color);


    virtual void render(Context *context, glm::vec3 position) override;

    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setColor(glm::vec3 c);
    glm::vec4 getColor();

private :
    void buildModelData(Context *context);

    GLfloat _r, _g, _b, _a; // red, green, blue, alpha components
};


#endif //LANGTON3D_RENDERABLECUBE_H
