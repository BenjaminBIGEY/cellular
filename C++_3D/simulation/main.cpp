#include <iostream>
#include "Simulation.h"
#include <map>

int main(int argc, char** argv) {
    Simulation simu;

    //simu.addAnt(10, 10, 10);
    simu.addAnt(0, 0, 0);

    simu.start(60);
    return 0;
}