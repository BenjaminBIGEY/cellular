//
// Created by benji on 10/11/16.
//

#include "Grid3D.h"

Cube::Cube(std::string name, std::shared_ptr<Unit> unit, std::shared_ptr<RenderableCube> render) : _buffer(name) {
    _unit = unit;
    _render = render;
}

void Cube::nextColor() {
    _unit->operator++(1);
}

void Cube::setColor(Color c) {
    _unit->setColor(c);
}

Color Cube::getColor() {
    return _unit->getColor();
}

void Cube::render(Context *context) {
    _render->render(context);
}

glm::vec3 Cube::getGraphicalPos() {
    return _render->getPosition();
}

//////////////////////////////////////////////////////////////////////////////////

Grid3D::Grid3D(int sizeX, int sizeY, int sizeZ, Color colorInit) {
    _grid.clear();

    for(int x = 0 ; x < sizeX ; x++) {
        std::deque<std::deque<Cube> > grid2D;

        for(int y = 0 ; y < sizeY ; y ++) {
            std::deque<Cube> v;

            for (int z = 0; z < sizeZ; z++) {
                // Add cube
                std::shared_ptr<Unit> unit = std::make_shared<Unit>(colorInit);
                std::shared_ptr<RenderableCube> cubeRender = std::make_shared<RenderableCube>();
                cubeRender->getMaterial().setDiffuse(1.0f, 1.0f, 1.0f);
                //cubeRender->addTexturePath("assets/cubeInit.png");

                v.emplace_back(Cube(std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z),
                                    unit,
                                    cubeRender));

            }
            grid2D.push_back(std::move(v));
        }
        _grid.push_back(std::move(grid2D));
    }
}

Grid3D::~Grid3D() {
    _grid[0][0].clear();
    _grid[0].clear();
    _grid.clear();
}

void Grid3D::update(Vector3 pos) {
    _grid[pos.x][pos.y][pos.z].nextColor();

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

void Grid3D::render(Context *context, int x, int y, int z) {
    _grid[x][y][y].render(context);
}

glm::vec3 Grid3D::getGraphicalPos(int x, int y, int z) {
    return _grid[x][y][z].getGraphicalPos();
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