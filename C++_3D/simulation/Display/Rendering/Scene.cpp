//
// Created by benji on 07/11/16.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"



Scene::Scene(std::shared_ptr<Grid3D> grid3D) : _camera(), _light() {
    _grid = grid3D;
}

void Scene::render(Context *context) {
    std::cout << "render de la scène appelé\n" << std::endl;

    int width, height;
    context->getWindowDimensions(width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    context->program().use();

    this->_camera.setRatio((float) width / height);
    this->_camera.updateCamera();
    this->_camera.setCameraView(context);

    glm::vec3 cubeGraphicalPos;

    for(int x = 0 ; x < _grid->getSizeX() ; x++) {
        for(int y = 0 ; y < _grid->getSizeY() ; y++) {
            for(int z = 0 ; z < _grid->getSizeZ() ; z++) {
                cubeGraphicalPos = _grid->getGraphicalPos(x, y, z);
                //_camera.moveCameraByCenterPoint(cubeGraphicalPos.x, cubeGraphicalPos.y, cubeGraphicalPos.z);

                _grid->render(context, x, y, z);
            }
        }
    }

    context->pushLight(_light);
    context->program().stopUsing();
}


void Scene::setLight(Light &light) {
    this->_light = light;
}