//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_SCENE_H
#define LANGTON3D_SCENE_H


#include <vector>
#include <memory>

#include "Camera.h"
#include "Context.h"
#include "Program.h"
#include "Renderable.h"
#include "../Grid3D.h"


class Camera;
class Context;
class Renderable;

class Scene {

public :
    Scene(std::shared_ptr<Grid3D> grid3D);

    Camera& getCamera() {return _camera;}

    void render(Context *context);

private :
    std::shared_ptr<Grid3D> _grid;
    Camera _camera;
};


#endif //LANGTON3D_SCENE_H
