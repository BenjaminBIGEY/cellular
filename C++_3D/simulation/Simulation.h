//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include "World/World.h"
#include "Display/Display.h"

class Simulation {
public:
    Simulation(int x, int y, int z, int nbrAnts);

    bool continueMainLoop();

private:
    std::unique_ptr<World> _world = nullptr;
    std::unique_ptr<Display> _display = nullptr;

    // Counter of moves
    int _count = 0;
};


#endif //LANGTON3D_SIMULATION_H
