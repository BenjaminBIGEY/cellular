//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_GRID3D_H
#define LANGTON3D_GRID3D_H

#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

#include "CubeMap.h"


class Grid3D {
public:
    Grid3D(Color colorInit, float alpha);
    ~Grid3D() {};

    void createCube(Vector3 position);

    void update(Vector3 position);

    void render(Context* context);

    Color getColor(Vector3 position);

    void setColor(Vector3 position, Color color);

    void setAlpha(Color color, float alpha);

    void debug();

    int getSize(){return _cubeMap.size();}
    //static const std::shared_ptr<Cube> _cubesPtr[Color::NBR];

private:
    // Container of the 3D grid of cubes
    CubeMap _cubeMap;
    // List of Cube ptr for optimization
    std::shared_ptr<Cube> _cubesPtr[Color::NBR];

    Color _colorInit;
};


#endif //LANGTON3D_GRID3D_H
