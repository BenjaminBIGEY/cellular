//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_SCENE_H
#define LANGTON3D_SCENE_H


#include <vector>
#include <memory>

#include "Camera.h"
#include "Light.h"

class Camera;
class Light;
class Context;
class Renderable;

class Scene {

public :
    Scene();

    Camera& getCamera() {return _camera;}

    void setLight(Light &light);

    void addObject(std::shared_ptr<Renderable> renderable);

    void render(Context *context);
private :
    Camera _camera;
    Light _light;

    std::vector<std::shared_ptr<Renderable>> _objects;
};


#endif //LANGTON3D_SCENE_H
