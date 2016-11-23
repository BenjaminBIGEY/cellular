//
// Created by benji on 10/11/16.
//

#include "Grid3D.h"

//const std::shared_ptr<Cube> _cubesPtr[Color::NBR];

Grid3D::Grid3D(Color colorInit, float alpha) {
    _colorInit = colorInit;

    // Construction of each cube with the specific color
    for(int i = 0 ; i < Color::NBR ; i++) {
        _cubesPtr[i] = std::make_shared<Cube>((Color)i, alpha);
        std::cout  << _cubesPtr[i] << "  ";
    }
    std::cout << "\n\n\n";
}


void Grid3D::createCube(Vector3 position) {
    // Check if the cube exists
    if(_cubeMap.find(position) == _cubeMap.end()) {
        _cubeMap[position] = _cubesPtr[_colorInit];
    }
}

void Grid3D::update(Vector3 position) {
    // No existing cube : we create it
    if(_cubeMap.find(position) == _cubeMap.end()) {
        createCube(position);
    } else {
        setColor(position, Cube::nextColor(getColor(position)));
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
    _cubeMap[pos] = _cubesPtr[(int)color];
}

void Grid3D::setAlpha(Color color, float alpha) {
    _cubesPtr[(int)color]->setAlpha(alpha);
}

void Grid3D::debug() {
    std::cout << "cube blanc : " << _cubesPtr[0] << "\ncube rouge : " << _cubesPtr[1] << "\n\n";
    CubeMapIterator it;
    for(it = _cubeMap.begin() ; it != _cubeMap.end() ; ++it) {
        // first <=> key : glm::vec3 (cubePosition)
        // second <=> mapped_type : std::shared_ptr<Cube>
        std::cout << "(" << it->first.x << "," << it->first.y << "," << it->first.z << ") contient ";
        if(it->second == _cubesPtr[0])
            std::cout << "BLANC\n";
        else if(it->second == _cubesPtr[1])
            std::cout << "ROUGE\n";
        else
            std::cerr << "NI ROUGE NI BLANC\n\n";
      }
}