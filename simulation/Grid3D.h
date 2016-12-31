//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_GRID3D_H
#define LANGTON3D_GRID3D_H

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <map>
#include <math.h>

#include "Message_Colors.h"
#include "Vector3.h"
#include "Elements/Rules.h"
#include "Rendering/RenderableCube.h"

#define SIZE_SUB_CUBE 30

using namespace std;

struct Unit;
struct CubeContainer;

class Grid3D {
public:
    Grid3D(){};
    ~Grid3D(){_grid3D.clear();};

    void reset(std::vector<Color> listColors);

    void update(Vector3 position, std::shared_ptr<Rules> rules);

    void render(Context *context);

    void addCube(Vector3 position, Color color);
    int getSize();
    int getMaxCoord();

    Color getColor();

    void debug();

private:
    // List of Cube ptr
    map<Color, std::shared_ptr<Unit>> _cubesPtr;

    // Container of the 3D grid of cubes
    std::map<Vector3, CubeContainer> _grid3D;

    // return TRUE if the generation is done ; FALSE else
    void generateSubCube();

    void updateCube(Color color);

    // position in the 3D array into the map
    void setCubePosition(Vector3 position);
    Vector3 _subCubePosition = Vector3(0, 0, 0);
    Vector3 _cubePosition = Vector3(0, 0, 0);

    std::map<Vector3, CubeContainer>::iterator currentIterator = _grid3D.begin();

    void drawSubCubes(Context *context, std::map<Vector3, CubeContainer>::iterator it, Color color);

    Color _colorInit;
};

struct CubeContainer {
    std::shared_ptr<Unit> subCube[SIZE_SUB_CUBE][SIZE_SUB_CUBE][SIZE_SUB_CUBE];
};

struct Unit {

    Unit(Color color,
         glm::vec3 ambient  = glm::vec3(0.85f, 0.25f, 0.1f),
         glm::vec3 diffuse  = glm::vec3(0.85f, 0.75f, 0.1f),
         glm::vec3 specular = glm::vec3(0.0f,  0.0f,  0.0f));

    void render(Context *context, Vector3 position);

    std::shared_ptr<RenderableCube> _render = nullptr;

    Color _color;
};

#endif //LANGTON3D_GRID3D_H
