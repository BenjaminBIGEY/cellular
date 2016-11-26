#include "simulation/Simulation.h"

int main(int argc, char** argv) {
    Simulation simu(PreConfiguredRules::X_Y_PLANE_2COLORS);

    /*simu.resetRules();
    simu.addRule("blue", GO_DOWN);
    simu.addRule(YELLOW, GO_UP);
    simu.initialize();*/

    simu.addAnt(0, 0, 0);

    simu.start();
    return 0;
}