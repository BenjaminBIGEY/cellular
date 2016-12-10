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
#include <map>
#include <math.h>

#include "Vector3.h"
#include "Elements/Rules.h"
#include "Rendering/RenderableCube.h"

using namespace std;

struct Cube;

class Grid3D {
public:
    Grid3D(const int radiusSphere = 100);
    ~Grid3D(){clear();};

    void clear();

    void reset(std::vector<Color> listColors);

    void update(Vector3 position, std::shared_ptr<Rules> rules);

    void render(Context *context);

    void setColor(Vector3 position, Color color);
    void createCube(Vector3 position, Color color);

    int getSize();
    int getSizeX(){return max(abs(_xMin), _xMax);}
    int getSizeY(){return max(abs(_yMin), _yMax);}
    int getSizeZ(){return max(abs(_zMin), _zMax);}

    Color getColor(Vector3 position);

    void checkEclatedView();

private:
    // Container of the 3D grid of cubes
    //CubeMap _cubeMap;
    // List of Cube ptr
    map<Color, std::shared_ptr<Cube>> _cubesPtr;
    std::vector<std::map<Vector3, std::shared_ptr<Cube>>> _cubeMap;
    std::vector<int> _normRadius;

    bool cubeIsExisting(const Vector3 position);
    int getRadius(const Vector3 position);

    Color _colorInit;
    int _xMin, _xMax, _yMin, _yMax, _zMin, _zMax = 0;

    bool _eclatedView = false;
};

struct Cube {

    Cube(Color color,
         glm::vec3 ambient  = glm::vec3(0.85f, 0.25f, 0.1f),
         glm::vec3 diffuse  = glm::vec3(0.85f, 0.75f, 0.1f),
         glm::vec3 specular = glm::vec3(0.0f,  0.0f,  0.0f));

    void render(Context *context, Vector3 position);

    std::shared_ptr<RenderableCube> _render = nullptr;

    Color _color;
};

#endif //LANGTON3D_GRID3D_H
