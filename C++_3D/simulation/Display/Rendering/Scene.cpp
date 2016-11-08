//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"
#include "Renderable.h"
#include "Context.h"
#include "Camera.h"
#include "Program.h"

Scene::Scene() : _camera(), _light() {

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
}

void Scene::stopUseContext(Context *context) {
    context->pushLight(_light);

    context->program().stopUsing();
}

void Scene::setLight(Light &light) {
    this->_light = light;
}
/*
void Scene::addObject(std::shared_ptr<Renderable> renderable) {
    _objects.push_back(std::shared_ptr<Renderable>(renderable));
}*/