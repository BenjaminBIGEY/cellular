//
// Created by benji on 24/10/16.
//

#include "Grid3D.h"

Grid3D::Grid3D(int sizeX, int sizeY, int sizeZ) {
    initGrid(sizeX, sizeY, sizeZ);
}

Grid3D::~Grid3D() {
    _grid[0][0].clear();
    _grid[0].clear();
    _grid.clear();
}

void Grid3D::initGrid(int sizeX, int sizeY, int sizeZ) {
    _grid.clear();

    // construction of X dimension
    for(int x = 0 ; x < sizeX ; x++) {
        std::deque<std::deque<Unit> > grid2D;
        // construction of Y dimension
        for(int y = 0 ; y < sizeY ; y ++) {
            std::deque<Unit> v;
            // construction of Z dimension
            for (int z = 0; z < sizeZ; z++) {
                v.emplace_back((Color) 0);
            }
            grid2D.push_back(std::move(v));
        }
        _grid.push_back(std::move(grid2D));
    }
}

void Grid3D::update(Vector3 pos) {
    _grid[pos.x][pos.y][pos.z]++;

    // TODO : case of the ant at the limit of the grid
}

int Grid3D::getSizeX() {
    return (int)_grid.size();
}

int Grid3D::getSizeY() {
    return (int)_grid[0].size();
}

int Grid3D::getSizeZ() {
    return (int)_grid[0][0].size();
}

Color Grid3D::getColor(Vector3 pos) {
    if(pos.x <= getSizeX() && pos.y <= getSizeY() && pos.z <= getSizeZ())
        return _grid[pos.x][pos.y][pos.z].getColor();

    std::cerr << "ERROR : the unit at ("  << pos.x << "," << pos.y << "," << pos.z << ") position doesn't exists" << std::endl;
    return (Color)0;
}

Color Grid3D::getColor(int x, int y, int z) {
    return getColor(Vector3(x,y,z));
}

void Grid3D::setColor(Vector3 pos, Color color) {
    if(pos.x <= getSizeX() && pos.y <= getSizeY() && pos.z <= getSizeZ())
        _grid[pos.x][pos.y][pos.z].setColor(color);
    else
        std::cerr << "ERROR : the unit at ("  << pos.x << "," << pos.y << "," << pos.z << ") position doesn't exists" << std::endl;
}

void Grid3D::setColor(int x, int y, int z, Color color) {
    setColor(Vector3(x,y,z), color);
}