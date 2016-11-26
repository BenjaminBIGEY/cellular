//
// Created by benji on 10/11/16.
//

#include "Grid3D.h"


Grid3D::Grid3D(std::vector<Color> listColors, float alpha) {
    reset(listColors, alpha);
}

void Grid3D::reset(vector<Color> listColors, float alpha) {
    _cubeMap.clear();

    _colorInit = listColors[0];

    for(auto color : listColors) {
        _cubesPtr[color] = std::make_shared<Cube>(color, alpha);
    }
}

void Grid3D::createCube(Vector3 position) {
    // Check if the cube exists
    if(_cubeMap.find(position) == _cubeMap.end()) {
        _cubeMap[position] = _cubesPtr[_colorInit];
    }
}

void Grid3D::update(Vector3 position, std::shared_ptr<Rules> rules) {
    // No existing cube : we create it
    if(_cubeMap.find(position) == _cubeMap.end()) {
        createCube(position);
    } else {
        setColor(position, rules->nextColor(getColor(position)));
    }
}

void Grid3D::render(Context *context) {
    CubeMapIterator it;
    for(it = _cubeMap.begin() ; it != _cubeMap.end() ; ++it) {
        // first <=> key : glm::vec3 (cubePosition)
        // second <=> mapped_type : std::shared_ptr<Cube>
        it->second->render(context, it->first);
    }
}

Color Grid3D::getColor(Vector3 pos) {
    if(_cubeMap.find(pos) != _cubeMap.end()) {
        return _cubeMap[pos]->_color;
    }

    return _colorInit;
}

void Grid3D::setColor(Vector3 pos, Color color) {
    _cubeMap[pos] = _cubesPtr[color];
}

void Grid3D::setAlpha(float alpha) {
    std::map<Color, std::shared_ptr<Cube>>::iterator it;

    for(it = _cubesPtr.begin() ; it != _cubesPtr.end() ; ++it) {
        _cubesPtr[it->first]->setAlpha(alpha);
    }
}