#include <iostream>
#include "Simulation.h"

int main(int argc, char** argv) {
    Simulation simu(5, 5, 5);

    //simu.addAnt(10, 10, 10);

    simu.setColor(2, 1, 1, Color::RED);

    simu.start(50);
    return 0;
}