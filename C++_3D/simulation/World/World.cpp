//
// Created by benji on 24/10/16.
//

#include "World.h"

World::World(int x, int y, int z) {
    _grid = make_unique<Grid3D>(x, y, z);
}

void World::addAnt(int x, int y, int z) {
    std::unique_ptr<Ant> ant = make_unique<Ant>(x, y, z, Orientation::FRONT);
    _listAnts.push_back(std::move(ant));
}

void World::update(useconds_t usec) {
    _display->update();

    Vector3 antPosition(0,0,0);
    Color newColor;
    for(int i = 0 ; i < _listAnts.size() ; i++) {
        antPosition = _listAnts[i]->getPosition();
        newColor = _grid->getColor(antPosition);
        //_listAnts[i]->update(newColor);

        _grid->update(antPosition);
        auto pos = _listAnts[i].get()->getPosition();
        //std::cout << "The ant is at position : X = " << pos.x << " ; Y = " << pos.y << " ; Z = " << pos.z << ".\n";

        // TODO
        //display(antPosition, newColor);
    }


    usleep(usec);

    _count++;
}

void World::debug() {
    std::cout << "The (x,y,z) size is : (" << _grid->getSizeX() << "," << _grid->getSizeY() << "," << _grid->getSizeZ() << ").\n\n";
    _grid->setColor(10, 15, 20, Color::ORANGE);
    std::cout << "The color of the (10,15,20) case is : " << _grid->getColor(10,15,20) << std::endl;
}