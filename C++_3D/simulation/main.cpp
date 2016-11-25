#include "Simulation.h"

int main(int argc, char** argv) {
    Simulation simu((Color)7);

    simu.addAnt(0, 0, 0);

    simu.start();
    return 0;
}