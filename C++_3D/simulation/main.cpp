#include <iostream>
#include "Simulation.h"


int main(int argc, char** argv) {
    Simulation simu(20, 20, 20);
    simu.addAnt(10, 10, 10);

    while(simu.continueSimulation()) {
        simu.mainLoop(1000);
    }

    return 0;
}