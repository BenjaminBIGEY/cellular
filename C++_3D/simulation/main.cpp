#include "Simulation.h"

int main(int argc, char** argv) {
    Simulation simu;

    simu.addAnt(0, 0, 0);

    simu.start(1);
    return 0;
}