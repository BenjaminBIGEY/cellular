//
// Created by benji on 08/11/16.
//

#include "Simulation.h"

Simulation::Simulation(int x, int y, int z, int nbrAnts) {

    // Initialization of Physic part
    _world = make_unique<World>(x, y, z);

    for(int i = 0 ; i < nbrAnts ; i++) {
        _world->addAnt(1, 2, 3);
    }

    // Initialization of Graphic part
    _display = make_unique<Display>();
    if(!_display->initGL())
        exit(EXIT_FAILURE);

    _display->initGrid(x, y, z);

    //_display->debug();
}

bool Simulation::continueMainLoop() {
    return _display->isWindowOpened();
}