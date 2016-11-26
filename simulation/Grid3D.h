//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_GRID3D_H
#define LANGTON3D_GRID3D_H

#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "CubeMap.h"

using namespace std;

class Grid3D {
public:
    Grid3D(vector<Color> listColors, float alpha);
    ~Grid3D() {};

    void reset(std::vector<Color> listColors, float alpha);

    void createCube(Vector3 position);

    void update(Vector3 position, std::shared_ptr<Rules> rules);

    void render(Context* context);

    Color getColor(Vector3 position);

    void setColor(Vector3 position, Color color);

    void setAlpha(float alpha);

    int getSize(){return _cubeMap.size();}

private:
    // Container of the 3D grid of cubes
    CubeMap _cubeMap;
    // List of Cube ptr
    map<Color, std::shared_ptr<Cube>> _cubesPtr;

    Color _colorInit;
};


#endif //LANGTON3D_GRID3D_H
