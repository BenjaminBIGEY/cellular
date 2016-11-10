//
// Created by benji on 10/11/16.
//

#ifndef LANGTON3D_GRID3D_H
#define LANGTON3D_GRID3D_H

#include <deque>
#include <glm/glm.hpp>
#include <iostream>

#include "Display/FileBuffer.h"
#include "Display/Rendering/RenderableCube.h"
#include "Elements/Unit.h"

struct Cube {
    Cube(std::string name, std::shared_ptr<Unit> unit, std::shared_ptr<RenderableCube> render);
    void nextColor();
    void setColor(Color c);
    Color getColor();

    void render(Context *context);

    glm::vec3 getGraphicalPos();

private:
    std::shared_ptr<Unit> _unit = nullptr;
    std::shared_ptr<RenderableCube> _render = nullptr;
    FileBuffer _buffer;
};


class Grid3D {
public:
    Grid3D(int sizeX, int sizeY, int sizeZ, Color colorInit = (Color)0);
    ~Grid3D();

    void update(Vector3 position);

    int getSizeX();
    int getSizeY();
    int getSizeZ();

    void render(Context* context, int x, int y, int z);
    glm::vec3 getGraphicalPos(int x, int y, int z);

    Color getColor(Vector3 position);
    Color getColor(int x, int y, int z);

    void setColor(Vector3 position, Color color);
    void setColor(int x, int y, int z, Color color);

private:
    std::deque<std::deque<std::deque<Cube>>> _grid;
};


#endif //LANGTON3D_GRID3D_H
