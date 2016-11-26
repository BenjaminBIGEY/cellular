//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>
#include <iostream>

#include "Scene.h"



Scene::Scene(std::shared_ptr<Grid3D> grid3D) : _camera() {
    _grid = grid3D;
}

void Scene::render(Context *context) {
    int width, height;
    context->getWindowDimensions(width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    context->program().use();

    this->_camera.setRatio((float) width / height);
    this->_camera.updateCamera();
    this->_camera.setCameraView(context);

    _grid->render(context);

    context->pushLight(_light);
    context->program().stopUsing();
}

void Scene::setLight(Light &light) {
    this->_light = light;
}