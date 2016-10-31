#include <iostream>
#include "World/World.h"
#include "World/World.h"


int main(int argc, char** argv) {
    World world(20, 20, 20);
    world.addAnt(10, 10, 10);

    while(world.continueMainLoop()) {
        world.update(50);
    }

    return 0;
}