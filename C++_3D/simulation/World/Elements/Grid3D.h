//
// Created by benji on 24/10/16.
//

#ifndef C_3D_GRID3D_H
#define C_3D_GRID3D_H

#include "Unit.h"

#include <deque>
#include <iostream>



class Grid3D {
public:
    Grid3D(int sizeX, int sizeY, int sizeZ);
    ~Grid3D();

    void update(Vector3 position);

    int getSizeX();
    int getSizeY();
    int getSizeZ();

    Color getColor(Vector3 position);
    Color getColor(int x, int y, int z);

    void setColor(Vector3 position, Color color);
    void setColor(int x, int y, int z, Color color);

private:
    void initGrid(int sizeX, int sizeY, int sizeZ);
    std::deque<std::deque<std::deque<Unit>>> _grid;
};


#endif //C_3D_GRID3D_H
